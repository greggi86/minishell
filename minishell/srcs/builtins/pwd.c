/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/17 15:44:14 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
