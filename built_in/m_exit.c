/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/16 15:35:17 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exit_cleanup(t_data *data)
{
	//close fds()
	//close processes
	//free everything()
	//execute Commad handles
	//return exitcode
}

// while != exit in main loop

int	m_exit(char *cmd, t_data *data)
{
	data->exit = 1;
	return (ft_atoi(cmd[0]));
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
