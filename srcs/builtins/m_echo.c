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

/*
new_line_check():	checks for newline flag (-n)

Arguments:			char **args

Return:				int 1 or 0

How it works:
				1. if no args return 1
				2. if first char of first arg is not '-' return 1
				3. while first arg from first char equal 'n' skip char
				4. if not all chars of fist arg are 'n' return 1
				5. return 0
*/
int	new_line_check(char **flags)
{
	int	i;

	i = 0;
	if(flags[i] == NULL || flags == NULL)
	{
		return (1);
	}
	if(flags[0][0] != '-')
		return (1);
	while (flags[0][i] == 'n')
	{
	i++;
	}
	if(flags[0][i] != 'n')
		return (1);
	return (0);
}

/*
m_echo():	echo command

Arguments:	t_cmd *cmd

Return:		void

How it works:
			1. starts index 0 arg
			2. newline std 1
			3. if first flag exist and newlinecheck 0(std case)
				4. newline = 0
*/
void	m_echo(t_cmd *cmd)
{
	int	start;
	int	newline;

	start = 0;
	newline = 1;
	if (cmd->flags[0] != NULL && new_line_check(cmd->flags) == 0)
	{
		newline = 0;
	}
	if (cmd->args[start] != NULL)
	{
		while (cmd->args[start] != NULL)
		{
			printf("%s", cmd->args[start]);
			if (cmd->args[start + 1])
				printf(" ");
			start++;
		}
	}
	if (newline)
		printf("\n");
}
