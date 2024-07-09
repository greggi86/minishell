/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:46 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/09 11:46:17 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_line_check(char **args)
{
	int	i;
	int	check;

	check = 0;
	i = 1;

	while (args[0][0] == '-' && args[0][i] == 'n')
	{
		i++;
	}
	if()
	return (0);
}

void	echo(t_cmd cmd)
{
	int	start;
	int	newline;

	start = 1;
	newline = 1;
	if (cmd.args[0] != NULL && new_line_check(cmd.args) == 0)
	{
		start++;
		newline = 0;
	}
	if (cmd.args[start] != NULL)
	{
		while (cmd.args[start] != NULL)
		{
			printf("%s", cmd.args[start]);
			if (cmd.args[start + 1])
				printf(" ");
			start++;
		}
	}
	if (newline)
		printf("\n");
}

