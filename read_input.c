/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:15:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 21:33:54 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(void)
{
	char *input;

	input = NULL;
	if (get_next_line(0, &input) == -1)
	{
		ft_error();
	}
	return (input);
}
