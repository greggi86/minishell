/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/12 18:06:06 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//implement tilde and home

int get_home(t_env **env)
{
	t_env	*i;
	t_env	*k;
	char	*path;

	i = *env;
	k = *env;
	while (i != NULL)
	{
		if (ft_strcmd(i->key, "HOME") == 0)
		{
			if (chdir(i->value) == 0)
			{
				path = getcwd(NULL, 0);
				while (k != NULL)
				{
					if (ft_strcmp(k->key, "PWD") == 0)
					{
						ft_strncpy(k->value, path, ft_strlen(path));
						return (0);
					}
					k = k->next;
				}
			}
		}
		i = i->next;
	}
	return (1);
}

void	change_directory(t_cmd *cmd)
{
	char	*old_pwd;
	char	*pwd;
	t_env	*i;

	old_pwd = getcwd(NULL, 0);
	i = cmd->env;
	while (i != NULL)
	{
		i = i->next;
		if (ft_strcmp(i->key, "OLDPWD") == 0)
			ft_strncpy(i->value, old_pwd, strlen(old_pwd));
	}
	i = cmd->env;
	if (ft_strcmp(cmd->args[0], '~') == 0)
	{
		if (get_home(cmd->env) == 0)
			return ;
	}
	if (chdir (cmd->args[0]) == 0)
	{
		pwd = getcwd(NULL, 0);
		while (i != NULL)
		{
			if (ft_strcmp(i->key, "PWD") == 0)
				ft_strncpy(i->value, pwd, strlen(pwd));
			i = i->next;
		}
		free(pwd);
	}
	else
	{
		perror("error on reading path");
	}
	free(old_pwd);
}

