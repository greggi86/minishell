/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:15:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/18 13:54:03 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal_status = 420;

int	set_env_lst(t_cmd *cmd_list,t_env *env)
{
	t_cmd *tmp;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		cmd_list->env = env;
		tmp = tmp->next;
	}
	return (0);
}


void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = signo;
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		g_signal_status = signo;
	}
}

int	bob_the_builder(char *input, t_env *env)
{
	char	**token_array;
	t_token	*token_list;
	t_cmd	*cmd_list;

	//split tokens
	token_array = split_tokens(input);
	if (!token_array)
		return (1);
	printf("After split:\n");
	print_str_array(token_array);
	printf("-----------------\n");
	//lexer / tokenization
	token_list = lexer(token_array);
	if (!token_list)
	{
		free_array(token_array);
		return (1);
	}
	printf("After lexing:\n");
	print_tokens(token_list);
	printf("-----------------\n");
	//syntax error check
	if (syntax_error(token_list))
	{
		free_array_and_tokens(token_array, token_list);
		return (1);
	}
	free_array(token_array);
	//parser
	token_list = env_expand(token_list);
	if (!token_list)
		return (1);
	printf("After env expand:\n");
	print_tokens(token_list);
	printf("-----------------\n");
	cmd_list = parser(token_list);
	if (!cmd_list)
	{
		free_tokens(token_list);
		return (1);
	}
	set_env_lst(cmd_list, env);
	printf("After parsing:\n");
	print_cmds(cmd_list);
	printf("-----------------\n");
	free_tokens(token_list);
	//execute cmd_list
	printf("output: \n");
	g_signal_status = exec_cmds(cmd_list);
	printf("exit status: %d\n", g_signal_status);
	free_cmd(cmd_list);
	//free / clean up
	return (g_signal_status);
}

int	minishell_loop(t_env *env)
{
	char	*input;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		input = readline(PROMPT);
		if (!input)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (*input)
		{
			add_history(input);
			exit_status = bob_the_builder(input, env);
		}
		free(input);
	}
	return (exit_status);
}

//int argc, char **argv
int	main(int ac, char **av, char **envp)
{

	t_env	*env_list;
	//t_env	*i;

	(void)ac;
	(void)av;

	env_list = NULL;
	parse_env(envp, &env_list);
	//i = env_list;
	//print_env_list(i);


	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	return (minishell_loop(env_list));
}
