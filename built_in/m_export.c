/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/16 17:17:43 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_export(char *cmd, t_data *data)
{
	int		i;
	int		j;
	int		len;
	char	**new_envp;

	i = 0;
	j = 0;
	len = 0;

	while (cmd[len])
		len++;

	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], cmd, len) == 0
			&& data->envp[i][len] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(cmd);
			return (0);
		}
		i++;
	}
	new_envp = malloc (sizeof(char *) * (i + 2));
	if (new_envp == NULL)
		return (-1);
	while (j < i)
	{
		new_envp[j] = data->envp[j];
		j++;
	}
	new_envp[i] = cmd;
	new_envp[i + 1] = NULL;
	return (0);

	while ()
	data->envp = new_envp;
	
}
