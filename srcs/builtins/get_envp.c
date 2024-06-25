/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:45:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/17 15:43:48 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_envp(t_data *data, char **envp)
{
	int	i;
	int	j;

	data->envc = 0;
	i = 0;
	j = 0;
	while (envp[data->envc] != NULL)
		data->envc++;
	if (data->envp != NULL)
	{
		while (data->envp != NULL)
		{
			free(data->envp[i]);
			i++;
		}
		free(data->envp);
		i = 0;
	}
	data->envp = malloc((data->envc + 1) * sizeof(char *));
	if (data->envp == NULL)
		perror("get_envp");
	while (i < data->envc)
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (data->envp[i] == NULL)
		{
			while (j < i)
			{
				free(data->envp[j]);
				j++;
			}
			free(data->envp);

		}
		i++;
	}
	envp[i] = NULL;
	return (data->envc);
}

