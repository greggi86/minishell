/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:18:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 13:04:32 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//add for "token"token cases
int	check_delimiter(char *input, int *in_quote, char *quote)
{
	if (*input == '\'' || *input == '\"')
	{
		if (*in_quote && *input == *quote)
			*in_quote = 0;
		else if (!*in_quote)
		{
			*quote = *input;
			*in_quote = 1;
		}
	}
	else if (!*in_quote && (*input == '|'
			|| *input == '<' || *input == '>' || ft_is_space(*input)))
		return (1);
	return (0);
}

int	count_tokens(char *input)
{
	int		in_quote;
	char	quote;
	int		count;
	int		in_token;

	count = 0;
	in_quote = 0;
	in_token = 0;
	quote = '\0';
	while (*input)
	{
		if (check_delimiter(input, &in_quote, &quote))
		{
			if (in_token)
			{
				count++;
				in_token = 0;
			}
			if (*input == '|' || *input == '<' || *input == '>')
			{
				count++;
				while (*input == '|' || *input == '<' || *input == '>')
					input++;
				continue ;
			}
		}
		else
			in_token = 1;
		input++;
	}
	if (in_token)
		count++;
	return (count);
}

char	*get_token(char **input)
{
	int		in_quote;
	char	quote;
	char	*start;
	char	*token;
	int		len;

	in_quote = 0;
	quote = '\0';
	start = *input;
	token = NULL;
	len = 0;
	while (**input)
	{
		if (check_delimiter(*input, &in_quote, &quote))
		{
			if (len > 0)
				break ;
			if (**input == '|' || **input == '<' || **input == '>')
			{
				start = *input;
				while (**input == '|' || **input == '<' || **input == '>')
					(*input)++;
				len = *input - start;
				break ;
			}
		}
		else
		{
			if (len == 0)
				start = *input;
			len++;
		}
		(*input)++;
	}
	token = (char *)malloc(len + 1);
	if (token)
	{
		ft_strncpy(token, start, len);
		token[len] = '\0';
	}
	return (token);
}

char	**split_tokens(char *input)
{
	int		token_count;
	char	**tokens;
	char	*token;
	int		i;

	token = NULL;
	i = 0;
	token_count = count_tokens(input);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (*input)
	{
		if (ft_is_space(*input))
		{
			input++;
			continue ;
		}
		token = get_token(&input);
		if (token)
		{
			tokens[i] = token;
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
