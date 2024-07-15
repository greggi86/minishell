/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:43:35 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/25 19:01:29 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//#define MAX_LINE_LEN 1024;

char	*ft_strstr(char *stack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return (stack);
	while (stack[i] != '\0')
	{
		while (stack[i + j] == needle[j])
		{
			if (needle[j + 1] != '\0')
				return (stack + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/*
int	check_heredoc(t_token *token_list, t_cmd *cmd)
{
	t_token	*heredocpos;

	heredocpos = token_list;
	while (heredocpos->word != NULL && heredocpos != NULL)
	{
		if (ft_strcmp(heredocpos->type, "HEREDOC") == 0)
		{
			heredocpos->next;
			//if(heredocpos != NULL)
			process_heredoc(heredocpos->word);
		}
		heredocpos->next;
	}
	return (0);
}
*/


size_t	readlines(int fd, char *buffer, size_t *maxlen)
{
	size_t	n;
	size_t	bytes_read;
	char	c;

	n = 0;
	if (!buffer || maxlen == 0)
		return (-1);
	if (buffer == NULL)
	{
		n = PATH_MAX;
		buffer = malloc(n);
		if (buffer == NULL)
			return (-1);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &c, 1);
		if (n < (*maxlen - 1))
		{
			buffer[n++] = c;
			if (c == '\n')
				break ;
		}
		else
			break ;
	}
	//if (bytes_read < 0)
	//	return (-1);
	if (bytes_read == 0 && n == 0)
		return (-1);
	else
		buffer[n] = '\0';
	return (*buffer);
}

int	process_heredoc(const char *delimiter)
{
	char	line[PATH_MAX];
	int		tmp_fd;
	size_t	len;
	size_t	readmax = 1024;

	tmp_fd = open("temp_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (tmp_fd < 0)
	{
		perror("open");
		return (-1);
	}
	while (1)
	{
		printf("heredoc->");
		len = readlines(STDERR_FILENO, line, &readmax);
		/*
		if (len < 0)
		{
			perror("readlines");
			close(tmp_fd);
			return (-1);
		}
		*/
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (strcmp(line, delimiter) == 0)
			break ;
		ft_strcat(line, "\n");
		if (write(tmp_fd, line, ft_strlen(line)) == -1)
		{
			perror("write");
			close(tmp_fd);
			return (-1);
		}
	}
	close(tmp_fd);
	return (0);
}
