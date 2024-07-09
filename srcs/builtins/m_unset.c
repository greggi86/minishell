/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:04 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:23 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while ((dstsize - 1) > i && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

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
	(*key)[i] = '\0';
	ft_strlcpy(*value, str + len + 1, ft_strlen(str + len + 1) + 1);
	printf("value: %s\n", *value);
	return (1);
}

int	add_to_env_export(t_cmd *cmd, char *str)
{
	t_env	*env;
	t_env	*new_node;
	char	*k;
	char	*v;

	if (!(split_env(str, &k, &v)))
		return (1);

	env = cmd->env;


	while (env != NULL)
	{
		if (ft_strncmp(env->key, k, ft_strlen(str) == 0))
		{
			free(env->value);
			env->value = v;
			free(k);
			return (0);
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		free(k);
		free(v);
		return (1);
	}
	new_node->key = k;
	new_node->value = v;
	new_node->next = NULL;
	if (cmd->env == NULL)
	{
		cmd->env = new_node;
	}
	else
	{
		env->next = new_node;
	}

	return (0);
}

int m_unset(t_cmd cmd, char *str) {
    t_env *i = cmd.env;
    t_env *prev = NULL;

    while (i != NULL) {
        if (ft_strncmp(i->key, str, ft_strlen(str) + 1) == 0) {
            if (prev == NULL) {  // Wenn es der erste Knoten ist
                cmd.env = i->next;
            } else {
                prev->next = i->next;
            }
            free(i->key);
            free(i->value);
            free(i);
            return 0;
        }
        prev = i;
        i = i->next;
    }
    return 0;
}


void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("Key: %s, Value: %s\n", env->key, env->value);
		env = env->next;
	}
}

int main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	t_cmd	cmd;

	cmd.env = NULL;
	s1 = "SONNE=Gut";
	s2 = "POLIZEI=Nichtso gut";
	s3 = "ESSEN=SEHR GUT";

	add_to_env_export(&cmd, s1);
	add_to_env_export(&cmd, s2);
	add_to_env_export(&cmd, s3);
	printf("vor unset: \n");
	print_env_list(cmd.env);
	printf("\n");
	m_unset(cmd, "POLIZEI");
	printf("nach unset \"POLIZEI\" \n");
	print_env_list(cmd.env);
	return (0);
}
