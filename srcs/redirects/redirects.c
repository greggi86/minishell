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
			// Implement here document redirection
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

void	close_pipes(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

char *find_command(char *cmd)
{
    char    *path_env;
    char    **paths;
    char    *full_path;
    int     i;

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
        if (!full_path)
            return (NULL);
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free(paths);
    return (NULL);
}

void	execute_command(t_cmd *cmd)
{
    char *full_path;

    full_path = find_command(cmd->cmd);
    if (!full_path)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    if (execve(full_path, cmd->args, NULL) == -1)
    {
        perror("execution error");
        exit(EXIT_FAILURE);
    }
    free(full_path);
}

int	exec_cmds(t_cmd *cmd_list)
{
	int		pipes[2];
	pid_t	pid;
	int		status;

	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(pipes);
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (cmd_list->prev)
				dup2(pipes[0], STDIN_FILENO);
			if (cmd_list->next)
				dup2(pipes[1], STDOUT_FILENO);
			execute_command(cmd_list);
		}
		if (cmd_list->prev)
			close_pipes(pipes);
		cmd_list = cmd_list->next;
	}
	while (wait(&status) > 0)
		;
	return (status);
}
