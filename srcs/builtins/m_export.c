/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/06 16:22:44 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_env *node)
{
	t_env	*tmp;

	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
}

void	add_env_node_back(t_env **envp, char *key, char *value)
{
	t_env	*node;
	t_env	*i;

	node = malloc(sizeof(t_env));
	node->key = strdup(key);
	node->value = strdup(value);
	node->next = NULL;

	if (*envp == NULL)
	{
		*envp = node;
	}
	else
	{
		i = *envp;
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = node;
	}
}

int	parse_env(char **envp, t_env **env)
{
	int		i;
	char	*entry;
	char	*key;
	char	*value;
	char	*equal_sign;

	i = 0;
	key = NULL;
	equal_sign = NULL;
	value = NULL;
	while (envp[i] != NULL)
	{
		entry = strdup(envp[i]);
		if (entry == NULL)
			return (1);
		equal_sign = strchr(entry, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			key = entry;
			value = equal_sign + 1;
		}
		else
		{
			key = entry;
			value = NULL;
		}
		add_env_node_back(env, key, value);
		i++;
	}
	return (0);
}

int	m_export(char *cmd, t_data *data)
{
	t_env	*node;
	t_env	*env;

	node = NULL;
	env = NULL;

	if (cmd != NULL || cmd[0] = '\0')
	{
		env = data->env;
		while(env)
		{
			if(env->value != NULL || env->value[0] != '\0')
			{
			printf ("declare -x %s=\"%s\"", env->key, env->value);
			env = env->next;
			}
			else
			{
				printf("declare -x %s");
				env = env->next;
			}
		}
		return (0);
	}
		if (parse_env(cmd, node) != 0)
			return (1);
		while (env != NULL)
		{
			if (ft_strncmp(data->env->key, cmd, strlen(cmd)) == 0)
			{
				free(env->value);
				data->env->value = ft_strdup(node->value);
				free_list(node);
				return (0);
			}
			env = env->next;
		}
	add_env_node_back(&(data->env), node->key, node->value);
	free_list(node);
	return (0);
}
