/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:59:35 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/30 20:48:10 by volyvar-         ###   ########.fr       */
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

// ~/Desktop
// ../Desktop
// ./libft

// /*
// ** old_pwd: /Users/volyvar/
// ** new_pwd: .. . ~ name /name ~/name ./ ../ ./name/name   ../name/name
// */
// char *ft_get_full_new_pwd(char *old_pwd, char *new_pwd) {//////////////CHANGE THIS FUNC ->PARSE
// 	char *full_pwd;
// 	char *tmp;

// 	if (!ft_strcmp(new_pwd, ".") || !ft_strcmp(new_pwd, "./")) {
// 		full_pwd = ft_strdup(old_pwd);
// 		return full_pwd;
// 	}
// 	if (!ft_strcmp(new_pwd, "..") || !ft_strcmp(new_pwd, "../")) {
// 		full_pwd = ft_path_step_back(old_pwd);
// 		return full_pwd;
// 	}
// 	if (new_pwd[0] == '/') {
// 		full_pwd = ft_strdup(new_pwd);
// 		return full_pwd;
// 	}
// 	if (new_pwd[0] != '/') {
// 		if (old_pwd[ft_strlen(old_pwd) - 1] == '/')
// 			return (ft_strconcat(old_pwd, new_pwd));
// 		else
// 			return (ft_strconcat_delim(old_pwd, new_pwd, "/"));
// 	}
// 	return NULL;
// }

void	ft_strswap(char **src, char **tmp) {
	ft_strdel(src);
	*src = ft_strdup(*tmp);
	ft_strdel(tmp);
}

/*
** old_pwd: /Users/volyvar/
** new_pwd: .. . ~ name /name ~/name ./ ../ ./name/name   ../name/name

/			+
/name		+

.
..
name
~			+ (early)

./name
../name
~/name

*/
char *ft_get_full_new_pwd(char *old_pwd, char *new_pwd, t_env *env) {//////////////CHANGE THIS FUNC ->PARSE
	char **piece_path;
	char *full_pwd;
	char *tmp;
	int i;
	char *home;

	if (new_pwd[0] == '/')
		return ft_strdup(new_pwd);

	piece_path = ft_strsplit(new_pwd, '/');

	i = 0;
	home = ft_strdup(ft_find_in_list(env, "HOME")->content);
	full_pwd = ft_strdup(old_pwd);
	while (piece_path[i]) {
		if (!ft_strcmp(piece_path[i], ".")) {
			i++;
			continue;
		} else if (!ft_strcmp(piece_path[i], "..")) {
			ft_path_step_back(&full_pwd);
		} else if (!ft_strcmp(piece_path[i], "~")) {
			// tmp = ft_strconcat_delim(full_pwd, home, "/");
			tmp = ft_strdup(home);
			ft_strswap(&full_pwd, &tmp);
		} else {
			tmp = ft_concat_path(full_pwd, piece_path[i]);
			// if (!ft_strcmp(full_pwd, "/"))
			// 	tmp = ft_strconcat(full_pwd, piece_path[i]);
			// else
			// 	tmp = ft_strconcat_delim(full_pwd, piece_path[i], "/");
			ft_strswap(&full_pwd, &tmp);
		}
		i++;
	}
	ft_strdel(&home);
	ft_free_after_split(piece_path);
	ft_strdel(piece_path);
	return full_pwd;

	// if (ft_arrlen(piece_path) == 1) { //ho parts
	// 	if (!ft_strdmp(new_pwd, "."))
	// 		return ft_strdup(old_pwd);
	// 	if 
	// }
	
	// char *full_pwd;
	// char *tmp;

	// if (!ft_strcmp(new_pwd, ".") || !ft_strcmp(new_pwd, "./")) {
	// 	full_pwd = ft_strdup(old_pwd);
	// 	return full_pwd;
	// }
	// if (!ft_strcmp(new_pwd, "..") || !ft_strcmp(new_pwd, "../")) {
	// 	full_pwd = ft_path_step_back(old_pwd);
	// 	return full_pwd;
	// }
	// if (new_pwd[0] != '/') {
	// 	if (old_pwd[ft_strlen(old_pwd) - 1] == '/')
	// 		return (ft_strconcat(old_pwd, new_pwd));
	// 	else
	// 		return (ft_strconcat_delim(old_pwd, new_pwd, "/"));
	// }
	// return NULL;
}

void	ft_change_oldpwd_and_pwd(t_env **env, char *new_pwd) {
	t_env *pwd;
	char *full_new_pwd;

	pwd = ft_find_in_list(*env, "PWD");
	if (pwd && pwd->content)
		ft_change_or_create_var(env, "OLDPWD", pwd->content);
	full_new_pwd = ft_get_full_new_pwd(pwd->content, new_pwd, *env);
	ft_change_or_create_var(env, "PWD", full_new_pwd);
}

void	ft_cd_go_to(t_env **env, char *dest_dir) {
	char *new_path;

	new_path = ft_get_full_new_pwd(ft_find_in_list(*env, "PWD")->content, dest_dir, *env);

	// concat full path
	if (chdir(new_path) == -1) {
		ft_printf("cd: no such file or directory: %s\n", dest_dir);
		return ;
	}
	ft_change_oldpwd_and_pwd(env, dest_dir);
}

void	ft_go_to_home_dir(t_env **env) {
	t_env *home;
	
	home = ft_find_in_list(*env, "HOME");
	if (home == NULL || home->content == NULL) // no HOME
		return ;
	ft_cd_go_to(env, home->content);
}

/*
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
void	ft_do_cd(char **command_parts, t_env **env) {
	t_env *tmp;
	char *contant;

	if (command_parts[1] == NULL || !ft_strcmp(command_parts[1], "~")) { // cd
		ft_go_to_home_dir(env);
		return ;
	}
	if (command_parts[1] && command_parts[2] == NULL) { // ONE ARG
		if (!ft_strcmp(command_parts[1], ".")) { //no need
			return ;
		}
		else if (!ft_strcmp(command_parts[1], "-")) {
			tmp = ft_find_in_list(*env, "OLDPWD");
			if (tmp && tmp->content) {
				contant = ft_strdup(tmp->content);
				ft_cd_go_to(env, contant);
				ft_strdel(&contant);
			}
		} else {
			ft_cd_go_to(env, command_parts[1]);
		}

		return ;
	}
	if (command_parts[1] && command_parts[2]) {
		ft_printf("cd: string not in pwd: %s\n", command_parts[2]);
		return ;
	}
}