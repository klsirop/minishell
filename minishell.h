/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:39 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/28 23:02:41 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include "./libft/includes/get_next_line.h"

typedef struct	s_env {
	char *name;
	char *content;
	struct s_env *next;
}				t_env;

/*
** read_input.c
*/

char *ft_read_input();

/*
** error.c
*/

void	ft_error();
void	ft_malloc_error();

/*
** free.c
*/

void	ft_free_after_split(char **arr);

/*
** do_command.c
*/

int ft_do_command(char *command, t_env **myenv);

/*
** ft_strsplit_sh.c
*/

char			**ft_strsplit_sh(char const *s, char c, char c1);

/*
** env.c
*/

void	ft_set_origin_env(t_env **myenv, char **env);
void	ft_print_env(t_env *myenv);
void	ft_do_setenv(char **command_parts, t_env **env);
void	ft_do_unsetenv(char **command_parts, t_env **env);
char *ft_remove_quotes(char *str);

/*
** list.c
*/

void	ft_list_add(t_env **head, char *name, char *content);
t_env		*ft_find_in_list(t_env *env, char *name);
void	ft_list_delete_element_name(t_env **head, char *name);

/*
** builtins.c
*/

void	ft_do_echo(char **command_parts, t_env *env);
char *ft_find_var(char *str, t_env *env);
void	ft_do_clear();
void	ft_do_help();
