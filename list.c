/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:47:12 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/05 16:17:37 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_add(t_env **head, char *name, char *content)
{
	t_env *tmp;
	t_env *go;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		ft_malloc_error();
	if (!(tmp->name = ft_strdup(name)))
		ft_malloc_error();
	if (!(tmp->content = ft_strdup(content)))
		ft_malloc_error();
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
	{
		go = *head;
		while (go->next)
			go = go->next;
		go->next = tmp;
	}
}

t_env		*ft_find_in_list(t_env *env, char *name) {
	t_env *tmp;

	tmp = env;
	while (tmp) {
		if (!ft_strcmp(tmp->name, name))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void	ft_list_delete_element_name(t_env **head, char *name)
{
	t_env *tmp;
	t_env *prev;

	prev = NULL;
	tmp = *head;
	while (tmp) {
		if (!ft_strcmp(tmp->name, name)) {
			if (prev == NULL) {
				*head = tmp->next;
				//delete
			} else {
				prev->next = tmp->next;
			}
			ft_strdel(&(tmp->name));
			ft_strdel(&(tmp->content));
			free(tmp);
			tmp = NULL;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}

}

int		ft_find_list_len(t_env *head)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
