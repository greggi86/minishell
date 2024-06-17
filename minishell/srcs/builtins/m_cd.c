/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/17 15:43:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

