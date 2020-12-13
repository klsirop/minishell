/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:14:01 by jmaynard          #+#    #+#             */
/*   Updated: 2020/12/13 19:24:55 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_refresh(char **rest, char *new)
{
	char	*tmp;

	if (ft_strlen(new) == 0)
	{
		free(*rest);
		*rest = NULL;
		return ;
	}
	if (!(tmp = ft_strdup(new)))
		return ;
	free(*rest);
	*rest = tmp;
}

char	*ft_n(const char *s)
{
	if (!s)
		return (NULL);
	while (*s != '\n' && *s != '\0' && *s != EOF)
	{
		s++;
	}
	if (*s == '\0' || *s == EOF)
		return (NULL);
	return ((char *)s);
}

int		ft_fill(char **line, char **rest, int flag)
{
	char *tmp;

	if (!(tmp = ft_n(*rest)))
	{
		if (!flag && !(*rest))
			return (0);
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	else
	{
		*line = ft_strsub(*rest, 0, tmp - *rest);
		ft_refresh(rest, tmp + 1);
	}
	if (!(*line))
		return (-1);
	return (1);
}

int		ft_read(char **rest, const int fd)
{
	char	*buff;
	int		flag;
	char	*tmp;

	buff = (char *)ft_memalloc(BUFF_SIZE + 1);
	flag = 0;
	while (!ft_n(*rest) && ((flag = read(fd, buff, BUFF_SIZE)) != 0))
	{
		if (flag == -1)
			return (-1);
		ft_bzero(buff + flag, (BUFF_SIZE + 1) - (size_t)flag);
		if (!(*rest))
			*rest = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(*rest, buff);
			free(*rest);
			*rest = tmp;
		}
		free(buff);
		if (!(buff = (char *)ft_memalloc(BUFF_SIZE + 1)) || !(*rest))
			return (-1);
	}
	free(buff);
	return (flag);
}

int		get_next_line(const int fd, char **line)
{
	char		*buff;
	static char	*rest;
	int			i;

	i = 0;
	buff = NULL;
	if (fd < 0 || BUFF_SIZE <= 0 || !line
		|| read(fd, buff, 0) < 0)
		return (-1);
	i = ft_read(&rest, fd);
	if (i == -1)
		return (-1);
	return (ft_fill(line, &rest, i));
}
