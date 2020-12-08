/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:15:46 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 20:45:35 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_read_input() {
	char *input;

	input = NULL;
	if (get_next_line(0, &input) == -1) {
		ft_error();
	}
	// ft_printf("input: || |%s|\n", input);
	// ft_printf("input len: %d\n", ft_strlen(input));
	return input;
}