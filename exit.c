/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:37:45 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 21:26:42 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_do_exit(char **command, uint8_t *exit_stat)
{
	int i;

	if (command[1] != NULL && command[2] != NULL)
	{
		ft_fprintf(2, GREEN_FON "minishell:" DROP
						BOLD " exit:" DROP " too many arguments\n");
		*exit_stat = 1;
		return (0);
	}
	else if (command[1] != NULL)
	{
		i = 0;
		while (command[1][i] != '\0')
		{
			if (!((i == 0 && command[1][i] == '-') ||
							(ft_isdigit(command[1][i]))))
			{
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD
							" exit:" DROP " numeric argument required\n");
				*exit_stat = 1;
				return (1);
			}
			i++;
		}
		*exit_stat = ft_atoi(command[1]);
	}
	return (1);
}
