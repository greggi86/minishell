/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/08 15:25:58 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//implement tilde and home

void	change_directory(t_cmd cmd)
{
	char	*old_pwd;
	char	*pwd;
	t_env	*i;

	old_pwd = getcwd(NULL, 0);
	i = cmd.env;
	while (i->key != "PWD" && i != NULL)
	{
		i = i->next;
	}
	if (i->key == "PWD")
		ft_strncpy(i->value, old_pwd, strlen(old_pwd));
	if (i->NULL)
	{
		add
	}
	if (chdir (cmd.cmd) == 0)
	{
		pwd = getcwd(NULL, 0);
		add_to_env(cmd.env, pwd);
		free(pwd);
	}
	else
	{
		perror("error on reading path");
	}
	free(old_pwd);
}

