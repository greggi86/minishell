/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/17 15:44:00 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_cleanup(t_cmd *data)
{
	(void) data;
	//close fds()
	//close processes
	//free everything()
	//execute Commad handles
	//return exitcode
	return (0);
}

// while != exit in main loop

int	m_exit(t_cmd *cmd)
{
	cmd->exit = 0;
	return (cmd->exit);
}

// int	m_exit(char *cmd, t_data *data)
// {
// 	int	exitcode;

// 	exitcode = 0;
// 	(void) *data;
// 	//exit_cleanup();
// 	if (cmd != NULL)
// 		exitcode = atoi(cmd);
// 	if (exitcode < 0 && exitcode > 255)
// 		exitcode %= 256;
// 	//convertion error?
// 	_exit(exitcode);
// }
