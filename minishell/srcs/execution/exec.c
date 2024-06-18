/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:37:13 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/18 13:44:29 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// •	Implement pipes (| character). The output of each command in the
// 		pipeline is connected to the input of the next command via a pipe.
// •	Handle $? which should expand to the exit status of the most recently
// 		executed foreground pipeline.
void	close_pipes(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

int	execute_command(t_cmd *cmd)
{
	char	*full_path;
	char	**merged;
	int		exit_status;

	merged = merge_args(cmd);
	full_path = find_command(cmd->cmd);
	exit_status = 0;
	if (!full_path)
	{
		printf("command not found \n");
		exit_status = 127;
		free_array(merged);
		free(full_path);
		return (exit_status);
	}
	if (execve(full_path, merged, NULL) == -1)
	{
		printf("execution error \n");
		exit_status = 126;
		free_array(merged);
		free(full_path);
	}
	free(full_path);
	free_array(merged);
	return (exit_status);
}

int	exec_cmds(t_cmd *cmd_list)
{
	int		pipes[2];
	int		prev_pipe_fd;
	pid_t	pid;
	int		status;
	int		last_status;
	int		exit_status;

	prev_pipe_fd = -1;
	last_status = 0;
	exit_status = 0;
	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipes) == -1)
		{
			printf("pipe error");
			g_signal_status = 1;
		}
		pid = fork();
		if (pid == -1)
		{
			printf("fork error");
			exit_status = 1;
		}
		if (pid == 0) // Child process
		{
			if (prev_pipe_fd != -1) // Not the first command
			{
				if (dup2(prev_pipe_fd, STDIN_FILENO) == -1)
				{
					printf("dup2 error on prev_pipe_fd");
					exit_status = 1;
				}
				close(prev_pipe_fd);
			}
			if (cmd_list->next) // Not the last command
			{
				if (dup2(pipes[1], STDOUT_FILENO) == -1)
				{
					printf("dup2 error on pipes[1]");
					exit_status = 1;
				}
				close(pipes[0]);
				close(pipes[1]);
			}
			exit_status = redirect_inputs(cmd_list);
			exit_status = redirect_outputs(cmd_list);
			exit_status = execute_command(cmd_list);
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
	return (exit_status);
}

/*
Sample execute:
int execute_command(char *input)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process
		char *argv[] = {"/bin/sh", "-c", input, NULL};
		execve("/bin/sh", argv, NULL);
		exit(127); // If execve fails
	}
	else if (pid < 0)
	{
		// Fork failed
		perror("fork");
		return 1;
	}
	else
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}
*/