/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:46 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/11 18:17:51 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	echo(char *str, t_data *data)
{
	int	start;
	int	newline;

	start = 1;
	newline = 1;
	(void)data;
	if (str[1] != NULL && ft_strcmp(str[0], "-n") == 0)
	{
		start ++;
		newline = 0;
	}
	if (str[start] != NULL)
	{
		while (str[start] != NULL)
		{
			printf("%s", str[start]);
			if (str[start + 1])
				printf(" ");
			start++;
		}
	}
	if (newline)
		printf("\n");
}

