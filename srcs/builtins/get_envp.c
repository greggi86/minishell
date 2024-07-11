/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:45:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/10 18:06:28 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		equal_sign = strchr(entry, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
		}
		key = entry;
		value = equal_sign + 1;
		add_env_node_back(env, key, value);
		i++;
	}
	return (0);
}


void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
//envp manipulation into key and value
int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	t_env	*i;

	(void)ac;
	(void)av;

	env_list = NULL;
	parse_env(envp, &env_list);
	i = env_list;
	print_env_list(i);
	return (0);
}
