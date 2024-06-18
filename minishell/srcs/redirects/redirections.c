/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:35:14 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/18 13:06:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Implement redirections:
// ◦	< should redirect input.	(DONE)
// ◦	> should redirect output.	(DONE)
// ◦	>> should redirect output in append mode.	(DONE)
// ◦	<< should be given a delimiter, then read the input until a line
//			containing the delimiter is seen. However, it doesn’t have to
// 			update the history!	(Not implemented)

int	handle_input(char *file)
{
	int	fd;
	int	exit_status;

	exit_status = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("input redirection error");
		exit_status = -1;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("dup2 error");
		exit_status = -1;
	}
	if (close(fd) == -1)
	{
		printf("close error");
		exit_status = -1;
	}
	return (exit_status);
}

int	handle_output(char *file)
{
	int	fd;
	int	exit_status;

	exit_status = 0;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("output redirection error");
		exit_status = -1;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2 error");
		exit_status = -1;
	}
	if (close(fd) == -1)
	{
		printf("close error");
		exit_status = -1;
	}
	return (exit_status);
}

int	handle_append(char *file)
{
	int	fd;
	int	exit_status;

	exit_status = 0;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("append redirection error");
		exit_status = -1;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2 error");
		exit_status = -1;
	}
	if (close(fd) == -1)
	{
		printf("close error");
		exit_status = -1;
	}
	return (exit_status);
}

int	redirect_inputs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		exit_status;

	tmp = cmd->infiles;
	exit_status = 0;
	while (tmp)
	{
		if (tmp->type == INPUT)
		{
			exit_status = handle_input(tmp->file);
		}
		if (tmp->type == HEREDOC)
		{
			// Implement here document redirection
		}
		tmp = tmp->next;
	}
	return (exit_status);
}

int	redirect_outputs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		exit_status;

	tmp = cmd->outfiles;
	exit_status = 0;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
		{
			exit_status = handle_output(tmp->file);
		}
		if (tmp->type == APPEND)
		{
			exit_status = handle_append(tmp->file);
		}
		tmp = tmp->next;
	}
	return (exit_status);
}
