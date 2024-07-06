/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/04 15:26:06 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//implement tilde and home

void	change_directory(t_data *data, char *cmd)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		free(new_pwd);
	}
	else
	{
		perror("error on reading path");
	}
	free(old_pwd);
}

