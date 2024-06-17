/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/15 22:31:53 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_pwd(char *cmd, t_data *data)
{
	char	*path[CHAR_MAX];

	(void)	*data;
	(void)	*cmd;

	if (getcwd(path, sizeof(path)) != 0)
	{
		ft_printf("%s", path);
	}
	else
	{
		perror( )      //error message neu;
	}
}
