/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:07:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/07 16:34:59 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_env(t_data *data)
{
	t_env	*env;

	env = data->env;

	while (env != NULL)
	{
		if (env->value != NULL || env->value[0] != '\0')
		{
			printf("%s=%s", env->key, env->value);
			env = env->next;
		}
		else
		{
			printf("%s", env->key);
			env = env->next;
		}
	}
	return (0);
}
