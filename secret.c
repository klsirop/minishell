/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:46:29 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 18:46:34 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_iamgay(char **command) {
	if (command[1] != NULL) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " iamgay: " DROP "too many arguments\n");
		return ;
	}
	if (g_promt == PROMT_GAY) {
		ft_printf("i know\n");
		return ;
	}
	ft_printf("me too 😏\n");
	g_promt = PROMT_GAY;
}

void	ft_iambi(char **command) {
	char *answer;

	if (command[1] != NULL) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " iambi: " DROP "too many arguments\n");
		return ;
	}
	if (g_promt == PROMT_SMILE) {
		ft_printf("i know\n");
		return ;
	}
	ft_printf("are you sure? [y/n]\n");
	if (get_next_line(0, &answer) == -1) {
		ft_error();
	}
	if (!ft_strcmp(answer, "y")) {
		g_promt = PROMT_SMILE;
		ft_strdel(&answer);
		return ;
	}
	if (!ft_strcmp(answer, "n")) {
		ft_strdel(&answer);
		return ;
	}
}
