/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/09 15:49:41 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//still to-do
//ascii order!!!
#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strdup(const char *str)
{
	char	*pstrt;
	char	*psrc;			
	char	*pdst;	

	pstrt = malloc(ft_strlen(str) + 1);
	psrc = (char *)str;
	pdst = pstrt;
	if (!pstrt)
	{
		return (NULL);
	}
	while (*psrc != 0)
	{
		*pdst = *psrc;
		pdst++;
		psrc++;
	}
	*pdst = '\0';
	return (pstrt);
}


char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;
	size_t			i;

	u_s1 = (unsigned char *) s1;
	u_s2 = (unsigned char *) s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (u_s1[i] != '\0' && u_s2[i] != '\0' && (i + 1 < n)
		&& u_s1[i] == u_s2[i])
	{
		i++;
	}
	return (u_s1[i] - u_s2[i]);
}

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

int	add_env_node_back(t_env **envp, char *key, char *value)
{
	t_env	*node;
	t_env	*i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (1);
	if (key != NULL)
		node->key = ft_strdup(key);
	else
		node->key = NULL;
	if (value != NULL)
		node->value = ft_strdup(value);
	else 
		node->value = NULL;
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
	return (0);
}

int parse_arg(char *envp, char **key, char **value)
{
    char *entry = ft_strdup(envp);
    if (!entry)
        return 1;
    char *equal_sign = ft_strchr(entry, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        *key = entry;
        *value = equal_sign + 1;
    }
    else
    {
        *key = entry;
        *value = NULL;
    }
    return 0;
}

int	m_export( t_cmd *cmd, char *str)
{
	t_env	*node;
	t_env	*env;

	node = NULL;
	env = NULL;

	if (cmd->cmd == NULL || cmd->cmd[0] == '\0')
	{
		env = cmd->env;
		while (env)
		{
			if (env->value != NULL || env->value[0] != '\0')
			{
				printf ("declare -x %s=\"%s\"\n", env->key, env->value);
				env = env->next;
			}
			else
			{
				printf("declare -x %s\n", env->key);
				env = env->next;
			}
		}
		return (0);
	}
	if (parse_arg(str, &node) != 0)
		return (1);
	while (env != NULL)
	{
		if (ft_strncmp(env->key, cmd->env->key, strlen(cmd->env->key)) == 0)
		{
			free(env->value);
			cmd->env->value = ft_strdup(node->value);
			free_list(node);
			return (0);
		}
		env = env->next;
	}
	add_env_node_back(&(env), node->key, node->value);
	free_list(node);
	return (0);
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("Key: %s, Value: %s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(void)
{
	t_cmd	cmd;
	char	*str;
	cmd.cmd = NULL;
	cmd.env = NULL;
	str = "EXPORT=megageil";

	m_export(&cmd, str);
	print_env_list(cmd.env);
	

}
