/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:07:57 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/18 13:18:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**merge_args(t_cmd *cmd)
{
	int		i;
	int		j;
	int		t_len;
	char	**merged;

	if (!cmd)
		return (NULL);
	t_len = 1 + array_len(cmd->args) + array_len(cmd->flags);
	merged = (char **)malloc(sizeof(char *) * (t_len + 1));
	if (!merged)
		return (NULL);
	i = 0;
	merged[i++] = ft_strdup(cmd->cmd);
	j = 0;
	while (cmd->args && cmd->args[j])
		merged[i++] = ft_strdup(cmd->args[j++]);
	j = 0;
	while (cmd->flags && cmd->flags[j])
		merged[i++] = ft_strdup(cmd->flags[j++]);
	merged[i] = NULL;
	return (merged);
}
