/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:37:41 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/04 15:24:17 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	check_builtins(t_cmd cmd)
{
	int			i;
	static void	*builtin[7][2] = {

	{"echo", m_echo},
	{"cd", m_cd},
	{"pwd", m_pwd},
	{"export", m_export},
	{"unset", m_unset},
	{"env", m_env},
	{"exit", m_exit},
	{0}
	};


	i = 0;

	while (i < 7)
	{
		if (ft_strcmp(cmd.cmd, builtin[i][0]) == 0)
		{
			return (builtin[i][1]);
		}
		i++;
	}
	return (1);
}
