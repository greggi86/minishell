/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:55:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/17 15:44:14 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
m_pwd():	prints working directory

Arguments:	char *cmd
			t_cmd *data

Return:		int errorcode

How it works:
			1. Initialize max path
			2. void arguments
			3. if getcwd ok
				4. print working directory
			5. else perror funky
			6. return 0
*/
int	m_pwd(t_cmd *cmd)
{
	char	path[CHAR_MAX];

	(void)	*cmd;

	if (getcwd(path, sizeof(path)) != 0)
	{
		printf("%s", path);
	}
	else
	{
		perror("funky");
	}
	return (0);
}
