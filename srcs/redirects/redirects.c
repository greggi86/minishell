/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:28:47 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 19:43:49 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_inputs(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->infiles;
	while (tmp)
	{
		if (tmp->type == INPUT)
		{
			int	fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
				perror("input redirection error");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (tmp->type == HEREDOC)
		{
			process_heredoc(tmp->file);
		}
		tmp = tmp->next;
	}
}

void	redirect_outputs(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->outfiles;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
		{
			int	fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				perror("output redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (tmp->type == APPEND)
		{
			int	fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				perror("append redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
}


