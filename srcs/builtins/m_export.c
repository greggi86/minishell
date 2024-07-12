/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/12 14:56:46 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//still to-do
//ascii order!!!
#include "minishell.h"

void add_env_node_back(t_env **envp, char *key, char *value)
{
	t_env *node;
	t_env *i;

	if (!key || !envp || !value)
	{
		return;
	}

	node = malloc(sizeof(t_env));
	if (node == NULL)
	{
		perror("d;s");
		exit(1);
	}
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
		while (i && i->next != NULL)
		{
			i = i->next;
		}
		if (i)
		{
			i->next = node;
		}
	}
}


int parse_env(char **envp, t_env **env)
{
	int i;
	char *entry;
	char *key;
	char *value;
	char *equal_sign;

	if (!env || !envp)
	{
		return (1);
	}

	i = 0;
	key = NULL;
	equal_sign = NULL;
	value = NULL;
	while (envp[i] != NULL)
	{
		entry = strdup(envp[i]);
		equal_sign = strchr(entry, '=');
		if (!equal_sign)
		{
			return (1);
		}
		else
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

void print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void print_env_list_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

int parse_arg(t_env *env, const char *str)
{
	const char *equal = strchr(str, '=');
	const char *key_start = str;
	const char *key_end = equal;
	const char *value_start = equal + 1;
	const char *value_end = str + strlen(str);

	if (key_start == key_end || value_start == value_end) {
		return (1);
	}

	char *key = strndup(key_start, key_end - key_start);
	char *value = strndup(value_start, value_end - value_start);

	env->key = key;
	env->value = value;

	return (0);
}

int get_env_length(t_env *env) {
    int i = 0;

    while (env) {
        env = env->next;
        i++;
    }
    return (i);
}

void lst_swap_next(t_env **env) {
    t_env *tmp;

    if (!env || !*env || !(*env)->next) {
        return;
    }
    tmp = (*env)->next;
    (*env)->next = (*env)->next->next;
    tmp->next = *env;
    (*env) = tmp;
}

void sort(t_env **env)
{
    t_env **a;
    int i;
    int len;

    if (!env || !*env || !(*env)->next) {
        return;
    }

    len = get_env_length(*env);
    while(len > 1)
    {
        a = env;
        i = 0;
        while(a != NULL && (*a)->next != NULL && i < len)
        {
            if (strcmp((*a)->key, (*a)->next->key) > 0) {
                lst_swap_next(a);
            }
            a = &(*a)->next;
            i++;
        }
        len--;
    }
}


int main(int ac, char **av, char **envp)
{
	t_env *env_list;
	t_env *node;
	char *str;

	(void) ac;
	(void) av;

	str = "hello=hallo";

    env_list = NULL;
	node = (t_env *) malloc(sizeof(t_env));
	if (node == NULL)
	{
		perror("malloc der Hurensohn wieder :(");
		return (1);
	}
	parse_env(envp, &env_list);

	int result = 0;
	if (parse_arg(node, str) != 0)
	{
		printf("parsing der Hurensohn wieder :(");
		result = 1;
	}
	//printf("key=%s | value=%s", node->key, node->value);
	free(node);
	//print_env_list(env_list);
    sort(&env_list);
    print_env_list_export(env_list);
	return (result);
}
