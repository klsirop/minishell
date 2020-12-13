/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:39 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/13 19:22:41 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef SYS_STAT_H
#  define SYS_STAT_H
#  include <sys/stat.h>
# endif
# ifndef SIGNAL_H
#  define SIGNAL_H
#  include <signal.h>
# endif
# ifndef LIBFT_INCLUDES_LIBFT_H
#  define LIBFT_INCLUDES_LIBFT_H
#  include "./libft/includes/libft.h"
# endif
# ifndef LIBFT_INCLUDES_FT_PRINTF_H
#  define LIBFT_INCLUDES_FT_PRINTF_H
#  include "./libft/includes/ft_printf.h"
# endif
# ifndef LIBFT_INCLUDES_FT_FPRINTF_H
#  define LIBFT_INCLUDES_FT_PRINTF_H
#  include "./libft/includes/ft_fprintf.h"
# endif
# ifndef LIBFT_INCLUDES_GET_NEXT_LINE_H
#  define LIBFT_INCLUDES_GET_NEXT_LINE_H
#  include "./libft/includes/get_next_line.h"
# endif

# define CLEAR "\033[?1049h\033[H"
# define UNCLEAR "\033[?1049l"

# define PROMT_SMILE 0x1F60F
# define PROMT_GAY 0x1F308

# define ITALIC "\033[0;3m"
# define BOLD "\033[1;1m"
# define DROP "\x1B[0m"

# define GREEN_FON "\e[48;5;78m\e[38;5;16m"
# define BLUE_FON "\033[1;1m\033[0;3m\e[48;5;123m\e[38;5;16m"
# define BOLD_PINK "\033[1;1m\e[38;5;161m"

# define PERMISSION_DENIED 126
# define NOT_EXISTS 127

typedef struct		s_env {
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

t_env				*g_env;
pid_t				g_pid;
int					g_promt;

/*
** read_input.c
*/

char				*ft_read_input();

/*
** error.c
*/

void				ft_error();
void				ft_malloc_error();

/*
** free.c
*/

void				ft_free_after_split(char **arr);
void				ft_free_env(t_env **env);

/*
** do_command.c
*/

int					ft_do_command(char *command,
						t_env **myenv, uint8_t *exit_stat);

/*
** ft_strsplit_sh.c
*/

char				**ft_strsplit_sh(char const *s, char c, char c1);

/*
** env.c
*/

void				ft_set_origin_env(t_env **myenv, char **env);
void				ft_print_env(char **command, t_env *myenv);
char				*ft_substitution(char *str, t_env *env);

/*
** set_unset_env.c
*/

void				ft_do_setenv(char **command_parts, t_env **env);
void				ft_do_unsetenv(char **command_parts, t_env **env);

/*
** list.c
*/

void				ft_list_add(t_env **head, char *name, char *content);
t_env				*ft_find_in_list(t_env *env, char *name);
void				ft_list_delete_element_name(t_env **head, char *name);
int					ft_find_list_len(t_env *head);

/*
** help.c
*/

void				ft_do_help();

/*
** echo.c
*/

void				ft_do_echo(char **command_parts, t_env *env);
char				*ft_find_var(char *str, t_env *env);
void				ft_do_clear(char **command);

/*
** cd.c
*/

void				ft_change_or_create_var(t_env **env,
						char *var_name, char *content);
int					ft_go_to_home_dir(t_env **env);
void				ft_change_oldpwd_and_pwd(t_env **env, char *new_pwd);
void				ft_strswap(char **src, char **tmp);

/*
** do_cd.c
*/

int					ft_do_cd(char **command_parts, t_env **env);
int					ft_cd_go_to(t_env **env, char *dest_dir);

/*
** get_full_pwd.c
*/

char				*ft_get_full_new_pwd(char *old_pwd,
						char *new_pwd, t_env *env);

/*
** manage_path.c
*/

char				*ft_create_str_from_split(char **arr, char c);
int					ft_arrlen(char **arr);
void				ft_path_step_back(char **old_path);

/*
** concat.c
*/

char				*ft_strconcat(char *s1, char *s2);
char				*ft_strconcat_delim(char *s1, char *s2, char *delim);
char				*ft_concat_path(char *s1, char *s2);

/*
** promt.c
*/

char				*ft_chrtoa_ostssrk(unsigned int chr);

/*
** process.c
*/

int					ft_do_process(char **command,
							t_env **env, uint8_t *exit_stat);

/*
** exit.c
*/

int					ft_do_exit(char **command, uint8_t *exit_stat);

/*
** remove_qoutes.c
*/

char				*ft_remove_quotes_echo(char *str);
char				*ft_remove_all_quotes(char *str);

/*
** secret.c
*/

void				ft_iamgay(char **command);
void				ft_iambi(char **command);

/*
** promt.c
*/

void				ft_print_this_dir(void);
void				ft_print_promt(void);

/*
** process_help.c
*/

void				ft_create_arr_env(char ***arr, t_env *env);
char				*ft_check_path_access(char *command, t_env *env);

#endif
