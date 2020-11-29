/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:08:02 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/29 19:53:25 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strconcat(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	int		j;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		ft_malloc_error();
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

/*
** create char *str from char **arr
** and separate each row by 'c'
** for example: we have arr[0] = /abc, arr[1] = bcd
** then str= /abc:bcd
*/
char *ft_create_str_from_split(char **arr, char c) {
	int len;
	int i;
	char *str;
	int j;
	int k;

	len = 0;
	i = 0;
	while (arr[i] != NULL) {
		len += ft_strlen(arr[i]);
		i++;
	}
	str = (char *)malloc(sizeof(char) * (len + i + 1));
	i = 0;
	k = 0;
	while (arr[i] != NULL) {
		j = 0;
		while (arr[i][j] != '\0') {
			str[k] = arr[i][j];
			j++;
			k++;
		}
		i++;
		if (arr[i] != NULL) {
			str[k] = c;
			k++;
		}
	}
	str[k] = '\0';
	return str;
}

/*
** return 's1/s2'
*/
char	*ft_strconcat_delim(char *s1, char *s2, char *delim)
{
	char *tmp;
	char *full;

	tmp = ft_strconcat(s1, delim);
	full = ft_strconcat(tmp, s2);
	ft_strdel(&tmp);
	return (full);
}

int	ft_arrlen(char **arr) {
	int i;

	i = 0;
	while (arr[i]) {
		i++;
	}
	return (i);
}

void	ft_print_arr(char **arr) {
	int i;

	i = 0;
	while (arr[i]) {
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

/*
** old_path = '/' ->return /
** old_path = '/usr' ->return /
** old_path = '/usr/bin' -> return /usr
** old_path = '/usr/bin/ -> return /usr
*/
char *ft_path_step_back(char *old_path) {
	char **piece_path;
	char *new_path;
	char *new_full_path;

	if (!ft_strcmp(old_path, "/")) {
		return (ft_strdup(old_path));
	}
	piece_path = ft_strsplit(old_path, '/');
	if (ft_arrlen(piece_path) == 1) {
		return ft_strdup("/");
	}
	ft_strdel(&(piece_path[ft_arrlen(piece_path) - 1]));
	new_path = ft_create_str_from_split(piece_path, '/');
	new_full_path = ft_strconcat("/", new_path);
	ft_free_after_split(piece_path);
	ft_strdel(piece_path);
	return (new_full_path);
}
