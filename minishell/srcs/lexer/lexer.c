/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:48:00 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/16 18:38:59 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*add_token(t_token *head, t_token *new_node)
{
	t_token	*tmp;

	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	return (head);
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

void	remove_empty_words(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->word[0] == '\0')
			tmp = remove_token(tmp);
		else
			tmp = tmp->next;
	}

}

void	merge_redirects(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE && tmp->next)
		{
			free(tmp->word);
			if (tmp->next->type == WORD
				&& !check_inner_chars(tmp->next->word, '|')
				&& !check_inner_chars(tmp->next->word, '>')
				&& !check_inner_chars(tmp->next->word, '<'))
			{
				tmp->word = ft_strdup(tmp->next->word);
				free(tmp->next->word);
				tmp->next->word = malloc(1 * sizeof(char));
				tmp->next->word[0] = '\0';
			}
			else
			{
				tmp->word = malloc(1 * sizeof(char));
				tmp->word[0] = '\0';
			}
		}
		tmp = tmp->next;
	}
}

t_token	*inject_token(t_token *prev, t_token *new_node, t_token *next)
{
	new_node->next = next;
	new_node->prev = prev;
	prev->next = new_node;
	next->prev = new_node;
	return (next);
}

t_token	*create_token(char *word, t_token_type type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = ft_strdup(word);
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	split_piperedir(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "|<") == 0)
		{
			free(tmp->word);
			tmp->word = ft_strdup("|");
			tmp->type = PIPE;
			tmp = inject_token(tmp, create_token("<", INPUT), tmp->next);
		}
		else if (ft_strcmp(tmp->word, "|>") == 0)
		{
			free(tmp->word);
			tmp->word = ft_strdup("|");
			tmp->type = PIPE;
			tmp = inject_token(tmp, create_token(">", OUTPUT), tmp->next);
		}
		else if (ft_strcmp(tmp->word, "|>>") == 0)
		{
			free(tmp->word);
			tmp->word = ft_strdup("|");
			tmp->type = PIPE;
			tmp = inject_token(tmp, create_token(">>", APPEND), tmp->next);
		}
		else if (ft_strcmp(tmp->word, "|<<") == 0)
		{
			free(tmp->word);
			tmp->word = ft_strdup("|");
			tmp->type = PIPE;
			tmp = inject_token(tmp, create_token("<<", HEREDOC), tmp->next);
		}
		tmp = tmp->next;
	}
}

t_token	*lexer(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*new_node;

	i = 0;
	head = NULL;
	new_node = NULL;
	while (tokens[i])
	{
		new_node = create_token(tokens[i], WORD);
		if (!new_node)
		{
			free_tokens(head);
			return (NULL);
		}
		head = add_token(head, new_node);
		i++;
	}
	set_types(head);
	split_piperedir(head);
	merge_redirects(head);
	remove_empty_words(head);
	return (head);
}
