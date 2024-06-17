/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:42:39 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/16 15:46:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_unclosed_quote(char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (!double_quotes)
				single_quotes = !single_quotes;
		}
		else if (*str == '"')
		{
			if (!single_quotes)
				double_quotes = !double_quotes;
		}
		str++;
	}
	if (single_quotes || double_quotes)
		return (1);
	else
		return (0);
}

int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

int	unclosed_quotes(char *str)
{
	if (check_unclosed_quote(str))
	{
		if (check_backslash(str))
			return (2);
		return (1);
	}
	return (0);
}
