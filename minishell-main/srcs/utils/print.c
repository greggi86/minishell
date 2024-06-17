/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:48:46 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 14:14:32 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("[%i] {%s}\n", i, arr[i]);
		i++;
	}
	printf("\n");
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;
	char	*type_str;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == WORD)
			type_str = "WORD";
		else if (tmp->type == INPUT)
			type_str = "INPUT";
		else if (tmp->type == OUTPUT)
			type_str = "OUTPUT";
		else if (tmp->type == HEREDOC)
			type_str = "HEREDOC";
		else if (tmp->type == APPEND)
			type_str = "APPEND";
		else if (tmp->type == PIPE)
			type_str = "PIPE";
		else
			type_str = "NO_TYPE";
		printf("Word: %s, Type: %s\n", tmp->word, type_str);
		tmp = tmp->next;
	}
}

void	print_redirs(t_redir *head)
{
	t_redir	*tmp;
	char	*type_str;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == INPUT)
			type_str = "INPUT";
		else if (tmp->type == OUTPUT)
			type_str = "OUTPUT";
		else if (tmp->type == HEREDOC)
			type_str = "HEREDOC";
		else if (tmp->type == APPEND)
			type_str = "APPEND";
		else
			type_str = "NO_TYPE";
		printf("File: %s, Type: %s\n", tmp->file, type_str);
		tmp = tmp->next;
	}
}

void	print_cmds(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		printf("PIPELINE NUMER: %i\n", i++);
		printf("CMD: %s\n", tmp->cmd);
		printf("ARGS:\n");
		print_str_array(tmp->args);
		printf("FLAGS:\n");
		print_str_array(tmp->flags);
		printf("INFILES:\n");
		print_redirs(tmp->infiles);
		printf("OUTFILES:\n");
		print_redirs(tmp->outfiles);
		tmp = tmp->next;
	}
}
