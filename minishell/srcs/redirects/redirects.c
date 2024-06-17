/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:28:47 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 19:22:36 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_inputs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->infiles;
	while (tmp)
	{
		if (tmp->type == INPUT)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{
				perror("input redirection error");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			if (close(fd) == -1)
			{
				perror("close error");
				exit(EXIT_FAILURE);
			}
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
	int		fd;

	tmp = cmd->outfiles;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("output redirection error");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			if (close(fd) == -1)
			{
				perror("close error");
				exit(EXIT_FAILURE);
			}
		}
		if (tmp->type == APPEND)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("append redirection error");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{	
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			if (close(fd) == -1)
			{
				perror("close error");
				exit(EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
}

void	close_pipes(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

////////////////////////////////////////////////////////////////////////////////

char	*find_command(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

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

//creates an array of strings with the command, arguments and flags
int get_array_length(char **array)
{
    int len;

    len = 0;
    while (array && array[len])
        len++;
    return (len);
}

char **merge_cmds_args_flags(t_cmd *cmd)
{
    int i;
    int j;
    int total_length;
    char **merged;

    if (!cmd)
        return (NULL);
    total_length = 1 + get_array_length(cmd->args) + get_array_length(cmd->flags);
    merged = (char **)malloc(sizeof(char *) * (total_length + 1));
    if (!merged)
        return (NULL);
    i = 0;
    merged[i++] = strdup(cmd->cmd);
    j = 0;
    while (cmd->args && cmd->args[j])
        merged[i++] = strdup(cmd->args[j++]);
    j = 0;
    while (cmd->flags && cmd->flags[j])
        merged[i++] = strdup(cmd->flags[j++]);
    merged[i] = NULL;
    return (merged);
}

void	execute_command(t_cmd *cmd)
{
	char	*full_path;
	char	**merged;

	merged = merge_cmds_args_flags(cmd);
	full_path = find_command(cmd->cmd);
	if (!full_path)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(full_path, merged, NULL) == -1)
	{
		perror("execution error");
		exit(EXIT_FAILURE);
	}
	free(full_path);
}

int exec_cmds(t_cmd *cmd_list)
{
	int     pipes[2];
	int     prev_pipe_fd = -1;
	pid_t   pid;
	int     status;
	int     last_status = 0;

	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipes) == -1)
		{
			perror("pipe error");
			g_signal_status = 1;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			g_signal_status = 1;
		}
		if (pid == 0) // Child process
		{
			if (prev_pipe_fd != -1) // Not the first command
			{
				if (dup2(prev_pipe_fd, STDIN_FILENO) == -1)
				{
					perror("dup2 error on prev_pipe_fd");
					exit(EXIT_FAILURE);
				}
				close(prev_pipe_fd);
			}
			if (cmd_list->next) // Not the last command
			{
				if (dup2(pipes[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 error on pipes[1]");
					exit(EXIT_FAILURE);
				}
				close(pipes[0]);
				close(pipes[1]);
			}
			redirect_inputs(cmd_list);
			redirect_outputs(cmd_list);
			execute_command(cmd_list);
		}

		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);

		if (cmd_list->next)
		{
			close(pipes[1]);
			prev_pipe_fd = pipes[0];
		}

		cmd_list = cmd_list->next;
	}

	while (wait(&status) > 0)
	{
		last_status = status;
	}
	g_signal_status = last_status;
	return (last_status);
}


// int	exec_cmds(t_cmd *cmd_list)
// {
// 	int		pipes[2];
// 	pid_t	pid;
// 	int		status;

// 	while (cmd_list)
// 	{
// 		if (cmd_list->next)
// 			pipe(pipes);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork error");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			if (cmd_list->prev)
// 				dup2(pipes[0], STDIN_FILENO);
// 			if (cmd_list->next)
// 				dup2(pipes[1], STDOUT_FILENO);
// 			execute_command(cmd_list);
// 		}
// 		if (cmd_list->prev)
// 			close_pipes(pipes);
// 		cmd_list = cmd_list->next;
// 	}
// 	while (wait(&status) > 0)
// 		;
// 	return (status);
// }

