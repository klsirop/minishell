/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:59:35 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/06 20:41:42 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_or_create_var(t_env **env, char *var_name, char *content) {
	t_env *tmp;

	tmp = ft_find_in_list(*env, var_name);
	if (tmp) {
		if (tmp->content)
			ft_strdel(&(tmp->content));
		tmp->content = ft_strdup(content);
	} else {
		ft_list_add(env, var_name, content);
	}
}

void	ft_strswap(char **src, char **tmp) {
	ft_strdel(src);
	*src = ft_strdup(*tmp);
	ft_strdel(tmp);
}

char *ft_get_full_new_pwd(char *old_pwd, char *new_pwd, t_env *env) {//////////////CHANGE THIS FUNC ->PARSE
	char **piece_path;
	char *full_pwd;
	char *tmp;
	int i;
	char *home;
	int is_abs;

	is_abs = 0;
	if (new_pwd[0] == '/') {
		is_abs = 1;
	}
	piece_path = ft_strsplit(new_pwd, '/');
	i = 0;
	home = ft_strdup(ft_find_in_list(env, "HOME")->content);
	if (!is_abs)
		full_pwd = ft_strdup(old_pwd);
	else
		full_pwd = ft_strdup("/");
	while (piece_path[i]) {
		if (!ft_strcmp(piece_path[i], ".")) {
			i++;
			continue;
		} else if (!ft_strcmp(piece_path[i], "..")) {
			ft_path_step_back(&full_pwd);
		} else if (!ft_strcmp(piece_path[i], "~")) {
			tmp = ft_strdup(home);
			ft_strswap(&full_pwd, &tmp);
		} else {
			tmp = ft_concat_path(full_pwd, piece_path[i]);
			ft_strswap(&full_pwd, &tmp);
		}
		i++;
	}
	ft_strdel(&home);
	ft_free_after_split(piece_path);
	free(piece_path);
	if (is_abs) {
		// tmp = ft_strconcat("/", full_pwd);
		return full_pwd;
	}
	return full_pwd;
}

void	ft_change_oldpwd_and_pwd(t_env **env, char *new_pwd) {
	t_env *pwd;
	char *full_new_pwd;

	pwd = ft_find_in_list(*env, "PWD");
	if (pwd && pwd->content)
		ft_change_or_create_var(env, "OLDPWD", pwd->content);
	full_new_pwd = ft_get_full_new_pwd(pwd->content, new_pwd, *env);
	ft_change_or_create_var(env, "PWD", full_new_pwd);
	ft_strdel(&full_new_pwd);
}

int		ft_cd_go_to(t_env **env, char *dest_dir) {
	char *new_path;
	struct stat status;

	new_path = ft_get_full_new_pwd(ft_find_in_list(*env, "PWD")->content, dest_dir, *env);

	if (chdir(new_path) == -1) {
		if (!lstat(new_path, &status)) {
			if (S_ISDIR(status.st_mode & S_IFMT))
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " cd: " DROP "permission denied:" DROP " %s\n", dest_dir);
			else if (S_ISLNK(status.st_mode & S_IFMT))
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " cd: " DROP "too many levels of symbolic links:" DROP " %s\n", dest_dir);
			else
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " cd: " DROP "not a directory: %s\n", dest_dir);
		}
		else
			ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " cd: " DROP "no such file or directory: %s\n", dest_dir);
		ft_strdel(&new_path);
		return (1);
	}
	ft_change_oldpwd_and_pwd(env, dest_dir);
	ft_strdel(&new_path);
	return (0);
}

int		ft_go_to_home_dir(t_env **env) {
	t_env *home;
	
	home = ft_find_in_list(*env, "HOME");
	if (home == NULL || home->content == NULL) // no HOME
		return (1);
	return (ft_cd_go_to(env, home->content));
}

/*
** cd $NAME
** cd 					: go to home dir ($HOME)
** cd . 				: do nothing
** cd .. 				: go early dir (use $PWD)
** cd name 				: go to name
** cd unvalid_name 		: "cd: no such file or directory: unvalid_name"
** cd ~ 				: gi to home dir ($HOME)
** cd -					: go to prev dir (use $OLDPWD)
** cd name1 name2		: replace name1 part in this name to name2 and try to go there
** manage ~/...
** manage changing OLDPWD and PWD
*/
int		ft_do_cd(char **command_parts, t_env **env) {
	t_env *tmp;
	char *contant;
	char *contant_no_quotes;
	char *after_substitution;
	int ret_code;

	ret_code = 0;
	if (command_parts[1] == NULL || !ft_strcmp(command_parts[1], "~")) {
		return (ft_go_to_home_dir(env));
	}
	if (command_parts[1] && command_parts[2] == NULL) {
		if (!ft_strcmp(command_parts[1], ".")) {
			return (0);
		}
		else if (!ft_strcmp(command_parts[1], "-")) {
			tmp = ft_find_in_list(*env, "OLDPWD");
			if (tmp && tmp->content) {
				contant = ft_strdup(tmp->content);
				ret_code = ft_cd_go_to(env, contant);
				ft_strdel(&contant);
			}
		} else {
			contant_no_quotes = ft_remove_quotes(command_parts[1]);
			after_substitution = ft_substitution(contant_no_quotes, *env);
			ret_code = ft_cd_go_to(env, after_substitution);
			ft_strdel(&contant_no_quotes);
			ft_strdel(&after_substitution);
		}

		return (ret_code);
	}
	if (command_parts[1] && command_parts[2]) {
		ft_printf(GREEN_FON "minishell:" DROP BOLD " cd: " DROP "string not in pwd: %s\n", command_parts[2]);
		return (1);
	}
	return (0);
}