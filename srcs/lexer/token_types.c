/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:30:02 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/16 14:32:59 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_types(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "<") == 0)
			tmp->type = INPUT;
		else if (ft_strcmp(tmp->word, ">") == 0)
			tmp->type = OUTPUT;
		else if (ft_strcmp(tmp->word, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->word, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->word, "|") == 0)
			tmp->type = PIPE;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}
