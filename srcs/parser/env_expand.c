/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:07:37 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 12:01:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *start, char *end)
{
	size_t	var_name_len;
	char	*var_name;

	var_name_len = end - start - 1;
	var_name = (char *)malloc(var_name_len + 1);
	if (!var_name)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(var_name, start + 1, var_name_len);
	var_name[var_name_len] = '\0';
	return (var_name);
}

char	*var_to_value(char *word, char *start, char *end, char *var_value)
{
	size_t	new_word_len;
	char	*new_word;

	new_word_len = ft_strlen(word) - (end - start - 1) + ft_strlen(var_value);
	new_word = (char *)malloc(new_word_len + 1);
	if (!new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(new_word, word, start - word);
	new_word[start - word] = '\0';
	ft_strcat(new_word, var_value);
	ft_strcat(new_word, end);
	return (new_word);
}

char	*expand_exit_status(char *word, char *start, char *end)
{
	char	*var_value;
	char	*new_word;

	var_value = (char *)malloc(12);
	if (!var_value)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_itoa(g_signal_status, var_value);
	new_word = var_to_value(word, start, end + 1, var_value);
	free(var_value);
	free(word);
	return (new_word);
}

char	*expand_env_variables(char *word)
{
	char	*start;
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*new_word;

	start = strchr(word, '$');
	if (!start)
		return (word);
	end = start + 1;
	if (*end == '?')
		return (expand_exit_status(word, start, end));
	while (*end && ((*end == '_') || ft_isalnum(*end)))
		end++;
	var_name = get_var_name(start, end);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	new_word = var_to_value(word, start, end, var_value);
	free(var_name);
	free(word);
	return (expand_env_variables(new_word));
}

////////////////////////////////////////////////////////////////////////////////

char	*ft_clean_quotes(char *word)
{
	char	*new_word;

	new_word = NULL;
	if (word[0] == '"' && word[ft_strlen(word) - 1] == '"')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		new_word = expand_env_variables(new_word);
		free(word);
		return (new_word);
	}
	else if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		free(word);
		return (new_word);
	}
	else
		return (word);
}

t_token	*env_expand(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		current->word = ft_clean_quotes(current->word);
		current = current->next;
	}
	return (head);
}