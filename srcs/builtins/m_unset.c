/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:04 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/06 16:55:50 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_unset(char *str, char ***envp)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp), str, len) == 0 && (*envp)[i][len] == '=')
		{
			free(*(envp[i]));
			i = j;
			while ((*envp)[j] != NULL)
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}


t_token	*remove_token(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->word);
	free(node);
	return (tmp);
}
