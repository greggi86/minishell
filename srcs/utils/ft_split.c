/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:29:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 13:41:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	st_count_words(char const *s, char separator)
{
	size_t	word_count;
	size_t	i;
	char	b_is_sep;
	char	b_was_sep;

	b_was_sep = 1;
	word_count = 0;
	i = 0;
	while (s[i])
	{
		b_is_sep = s[i] == separator;
		if (!b_is_sep && b_was_sep)
			word_count++;
		i++;
		b_was_sep = b_is_sep;
	}
	return (word_count);
}

static void	st_handle_word(char const *s, size_t *char_i,
								char separator, char **dest)
{
	size_t	word_start_idx;
	size_t	write_i;

	while (s[*char_i] == separator)
		*char_i += 1;
	word_start_idx = *char_i;
	while (s[*char_i] && s[*char_i] != separator)
		*char_i += 1;
	*dest = malloc((*char_i - word_start_idx) + 1);
	if (*dest)
	{
		write_i = 0;
		while (write_i < (*char_i - word_start_idx))
		{
			(*dest)[write_i] = s[word_start_idx + write_i];
			write_i++;
		}
		(*dest)[*char_i - word_start_idx] = '\0';
	}
}

static void	st_abort(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;
	size_t	word_count;
	size_t	word_i;
	size_t	char_i;

	if (s == NULL)
		return (NULL);
	word_count = st_count_words(s, c);
	new_array = malloc(sizeof(*new_array) * (word_count + 1));
	if (new_array == NULL)
		return (NULL);
	char_i = 0;
	word_i = 0;
	while (word_i < word_count)
	{
		st_handle_word(s, &char_i, c, &new_array[word_i]);
		if (new_array[word_i] == 0)
		{
			st_abort(new_array);
			return (0);
		}
		word_i++;
	}
	new_array[word_count] = 0;
	return (new_array);
}