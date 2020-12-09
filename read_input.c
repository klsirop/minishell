/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:15:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/09 14:01:32 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(void)
{
	char *input;
	int ret = 100;

	input = NULL;
	// ft_printf("read");
	if ((ret = get_next_line(0, &input)) == -1)
	{
		// ft_printf("d\n");
		ft_error();
	}
	if (ret == 0) {
		// exit(0);
		ft_printf("\n");
	}
	// ft_printf("ret gnl = %d\n", ret);
	// ft_printf("input = |%s|\n", input);
	return (input);
}
