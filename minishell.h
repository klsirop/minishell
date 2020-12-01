/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:39 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/01 18:52:30 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include "./libft/includes/ft_fprintf.h"
#include "./libft/includes/get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CLEAR "\033[?1049h\033[H"
#define UNCLEAR "\033[?1049l"

#define PROMT_SMILE 0x1F60F
#define PROMT_GAY 0x1F308

#define ITALIC "\033[0;3m"
#define BOLD "\033[1;1m"
#define DROP "\x1B[0m"

#define GREEN_FON "\e[48;5;78m"
#define LIGHT_BLUE_FON "\e[48;5;123m"

#define BLACK_TEXT "\e[38;5;16m"

int g_promt;

typedef struct	s_env {
	char *name;
	char *content;
	struct s_env *next;
}				t_env;

t_env *g_env;

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
void	ft_print_env(char **command, t_env *myenv);
void	ft_do_setenv(char **command_parts, t_env **env);
void	ft_do_unsetenv(char **command_parts, t_env **env);
char *ft_remove_quotes(char *str);
char *ft_substitution(char *str, t_env *env);

/*
** list.c
*/

void	ft_list_add(t_env **head, char *name, char *content);
t_env		*ft_find_in_list(t_env *env, char *name);
void	ft_list_delete_element_name(t_env **head, char *name);
int		ft_find_list_len(t_env *head);

/*
** builtins.c
*/

void	ft_do_echo(char **command_parts, t_env *env);
char *ft_find_var(char *str, t_env *env);
void	ft_do_clear(char **command);
void	ft_do_help();

/*
** cd.c
*/

void	ft_change_or_create_var(t_env **env, char *var_name, char *content);
void	ft_do_cd(char **command_parts, t_env **env);

/*
** manage_path.c
*/

char	*ft_strconcat(char *s1, char *s2);
char *ft_create_str_from_split(char **arr, char c);
int	ft_arrlen(char **arr);
char	*ft_strconcat_delim(char *s1, char *s2, char *delim);
void	ft_print_arr(char **arr);
char *ft_concat_path(char *s1, char *s2);
void	ft_path_step_back(char **old_path);
char *ft_concat_path(char *s1, char *s2);

/*
** promt.c
*/

char		*ft_chrtoa_ostssrk(unsigned int chr);

/*
** process.c
*/

int		ft_do_process(char **command_parts, t_env **env);

/*
** mysplit.c
*/

char					**ft_strsplit_my(char const *s, char c);
