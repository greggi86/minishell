/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:03:56 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/08 15:00:40 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split_env(char *str, char **key, char **value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	if (str[len] == '\0')
		return (0);
	*key = (char *)malloc((len + 1) * sizeof(char));
	*value = (char *)malloc((ft_strlen(str) - len) * sizeof(char));
	if (*key == NULL || *value == NULL)
		return (0);
	while (i < len)
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i] == '\0';
	ft_strcpy(*value, str + len + 1);
	return (1);
}

int	add_to_env_export(t_cmd cmd, char *str)
{
	t_env	*env;
	char	*k;
	char	*v;

	env = cmd.env;
	split_env(str, &k, &v);
	while (ft_strcmp(env->key, k) != 0 && env != NULL)
	{
		env = env->next;
	}
	if (ft_strcmp(env->key, k) == 0)
	{
		ft_strncpy(env->value, v, ft_strlen(v));
		return (0);
	}
	else
	{
		ft_strncpy(env->value, v, ft_strlen(v));
		ft_strncpy(env->key, k, ft_strlen(k));
	}
	return (1);
}
