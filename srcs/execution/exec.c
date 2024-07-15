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
#include <string.h>

// •	Implement pipes (| character). The output of each command in the
// 		pipeline is connected to the input of the next command via a pipe.
// •	Handle $? which should expand to the exit status of the most recently
// 		executed foreground pipeline.
void	close_pipes(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

int	builtins_caller(t_cmd *cmd)
{
	printf("command: <%s>\n\n", cmd->cmd);

	if (strcmp(cmd->cmd, "echo") == 0)
	{
		m_echo(cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "cd") == 0)
	{
		printf("ENTERED CD");
		m_cd(cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "pwd") == 0)
	{
		m_pwd(cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "export") == 0)
	{
		//m_export(cmd);
		printf("do export");
		return (1);
	}
	else if (strcmp(cmd->cmd, "unset") == 0)
	{
		m_unset(cmd, cmd->args[0]);
		return (1);
	}
	else if (strcmp(cmd->cmd, "env") == 0)
	{
		m_env(cmd);
		return(1);
	}
	else if (strcmp(cmd->cmd, "exit") == 0)
	{
		m_exit(cmd);
		return(1);
	}
	return (0);
}

int	execute_command(t_cmd *cmd)
{
	char	*full_path;
	char	**merged;
	int		exit_status;

	merged = merge_args(cmd);
	exit_status = 0;
	if (builtins_caller(cmd) == 1)
	{
		//free(full_path);
		free_array(merged);
		return (exit_status);
	}



	full_path = find_command(cmd->cmd);
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
		return(exit_status);
	}
	free(full_path);
	free_array(merged);
	exit_status = 126;
	return (exit_status);
}

//add builtins before fork
int	exec_cmds(t_cmd *cmd_list)
{
	int		pipes[2];
	//int		prev_pipe_fd;
	//pid_t	pid;
	int		status;
	int		last_status;
	int		exit_status;

	//prev_pipe_fd = -1;
	last_status = 0;
	exit_status = 0;
	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipes) == -1)
		{
			printf("pipe error");
			g_signal_status = 1;
		}
		//pid = fork();
		/*
		if (pid == -1)
		{
			printf("fork error");
			exit_status = 1;
		}
		*/
		execute_command(cmd_list);
		/*
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
			redirect_inputs(cmd_list);
			redirect_outputs(cmd_list);
			exit_status = execute_command(cmd_list);
		}
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (cmd_list->next)
		{
			close(pipes[1]);
			prev_pipe_fd = pipes[0];
		}
		*/
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

/*
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
*/
