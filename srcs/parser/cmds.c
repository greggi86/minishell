/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:43:14 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 14:02:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*add_node(t_cmd *head, t_cmd *new_node)
{
	t_cmd	*last;

	if (!head)
		return (new_node);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (head);
}

t_redir	*add_redir(t_redir *head, t_redir *new_node)
{
	t_redir	*last;

	if (!head)
		return (new_node);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (head);
}

t_redir	*get_infiles(t_token *head)
{
	t_redir	*infiles;
	t_token	*tmp;
	t_redir	*new_node;

	infiles = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			new_node = (t_redir *)malloc(sizeof(t_redir));
			new_node->file = ft_strdup(tmp->word);
			new_node->type = tmp->type;
			new_node->next = NULL;
			infiles = add_redir(infiles, new_node);
		}
		tmp = tmp->next;
	}
	return (infiles);
}

t_redir *get_outfiles(t_token *head)
{
	t_redir	*outfiles;
	t_token	*tmp;
	t_redir	*new_node;

	outfiles = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			new_node = (t_redir *)malloc(sizeof(t_redir));
			new_node->file = ft_strdup(tmp->word);
			new_node->type = tmp->type;
			new_node->next = NULL;
			outfiles = add_redir(outfiles, new_node);
		}
		tmp = tmp->next;
	}
	return (outfiles);
}

char	**get_args(t_token *head)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	args = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && !(strncmp(tmp->word, "-", 1) == 0))
			i++;
		tmp = tmp->next;
	}
	args = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			head = head->next;
			break ;
		}
		head = head->next;
	}
	while (head && head->type != PIPE)
	{
		if (head->type == WORD && !(strncmp(head->word, "-", 1) == 0))
		{
			args[i] = ft_strdup(head->word);
			i++;
		}
		head = head->next;
	}
	args[i] = NULL;
	return (args);
}

char	**get_flags(t_token *head)
{
	char	**flags;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	flags = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && strncmp(tmp->word, "-", 1) == 0)
			i++;
		tmp = tmp->next;
	}
	flags = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			head = head->next;
			break ;
		}
		head = head->next;
	}
	while (head && head->type != PIPE)
	{
		if (head->type == WORD && strncmp(head->word, "-", 1) == 0)
		{
			flags[i] = ft_strdup(head->word);
			i++;
		}
		head = head->next;
	}
	flags[i] = NULL;
	return (flags);
}

char	*get_cmd(t_token *head)
{
	char	*cmd;

	cmd = NULL;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			cmd = ft_strdup(head->word);
			break ;
		}
		head = head->next;
	}
	return (cmd);
}

t_cmd	*create_node(t_token *head)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = get_cmd(head);
	new_node->args = get_args(head);
	new_node->flags = get_flags(head);
	new_node->infiles = get_infiles(head);
	new_node->outfiles = get_outfiles(head);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*parser(t_token *head)
{
	t_cmd	*cmds;
	t_token	*tmp;
	t_cmd	*new_node;

	cmds = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp)
	{
		new_node = create_node(head);
		cmds = add_node(cmds, new_node);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (!tmp)
			break ;
		if (tmp->type == PIPE)
			tmp = tmp->next;
		head = tmp;
		tmp = tmp->next;
	}
	return (cmds);
}
