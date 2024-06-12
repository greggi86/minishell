/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/11 16:52:46 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//implement tilde and home

void	change_directory(t_data *data, char *cmd)
{
	char	*current_directory;
	char	*new_directory;

	current_directory = getcwd(NULL, 0);
	if (chdir(cmd) == 0)
	{
		new_directory = getcwd(NULL, 0);
		free(new_directory);
	}
	else
	{
		perror("error on reading path");
	}
	free(current_directory);
}

