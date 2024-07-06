/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:45:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/05 16:41:52 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"

// int	get_envp(t_data *data, char **envp)
// {
// 	int	i;
// 	int	j;

// 	data->envc = 0;
// 	i = 0;
// 	j = 0;
// 	while (envp[data->envc] != NULL)
// 		data->envc++;
// 	if (data->envp != NULL)
// 	{
// 		while (data->envp != NULL)
// 		{
// 			free(data->envp[i]);
// 			i++;
// 		}
// 		free(data->envp);
// 		i = 0;
// 	}
// 	data->envp = malloc((data->envc + 1) * sizeof(char *));
// 	if (data->envp == NULL)
// 		perror("get_envp");
// 	while (i < data->envc)
// 	{
// 		data->envp[i] = ft_strdup(envp[i]);
// 		if (data->envp[i] == NULL)
// 		{
// 			while (j < i)
// 			{
// 				free(data->envp[j]);
// 				j++;
// 			}
// 			free(data->envp);

// 		}
// 		i++;
// 	}
// 	envp[i] = NULL;
// 	return (data->envc);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

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

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("Key: %s, Value: %s\n", env->key, env->value);
		env = env->next;
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
