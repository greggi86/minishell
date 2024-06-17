/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:12:15 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 19:16:20 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[32mminishell> \033[0m"
# define PATH_MAX 1024;

//////////////////////////
// Include dependencies //
//////////////////////////
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <curses.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto,
								//tputs
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // perror
# include <fcntl.h>             // access, open, read, close
# include <readline/history.h>  // add_history
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset,
								//kill
# include <stdio.h>             // printf
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/ioctl.h>         // ioctl
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // fork, wait, waitpid, wait3, wait4
# include <sys/wait.h>          // wait, waitpid, wait3, wait4
# include <termios.h>           // isatty, ttyname, ttyslot, tcsetattr,
								//tcgetattr
# include <unistd.h>            // write, getcwd, chdir, unlink, execve, dup,
								//dup2, pipe
# include <limits.h>            // PATH_MAX

//////////////////////////
//   Global Variables   //
//////////////////////////
extern int	g_signal_status;

//////////////////////////
// Data structure types //
//////////////////////////
typedef enum e_token_type
{
	WORD = 0,
	INPUT = 1,
	OUTPUT = 2,
	HEREDOC = 3,
	APPEND = 4,
	PIPE = 5,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*file;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**flags;
	t_redir			*infiles;
	t_redir			*outfiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

// typedef struct s_data
// {
// 	char	*cmd;
// 	int		exit;
// 	int		*state;
// 	char	*flag;
// 	char	**env;
// 	int		envc;
// }		t_data;

// ////////////////////////////////////////////////////
// typedef int	(*t_builtin_func)(char *cmd, t_data *data);

// typedef struct s_builtin
// {
// 	char			*cmd;
// 	t_builtin_func	func;
// } t_builtin

// static const s_builtin g_builtin[] = {

// 	{"echo", m_echo},
// 	{"cd", m_cd},
// 	{"pwd", m_pwd},
// 	{"export", m_export},
// 	{"unset", m_unset},
// 	{"env", m_env},
// 	{"exit", m_exit},
// 	{0}
// }	t_builtin;

//////////////////////////////////
//		Function prototypes		//
//////////////////////////////////
//////////////////////////
//		builtins		//
//////////////////////////
// int		m_echo(char *cmd, t_data *data);
// int		m_cd(char *cmd, t_data *data);
// int		m_env(char *cmd, t_data *data);
// int		m_pwd(char *cmd, t_data *data);
// int		m_exit(char *cmd, t_data *data);
// int		m_export(char *cmd, t_data *data);

//////////////////////////
//		cleaners		//
//////////////////////////
// cleaners.c
void	free_array(char **arr);
void	free_tokens(t_token *head);
void	free_array_and_tokens(char **arr, t_token *head);
void	free_cmd(t_cmd *head);

//////////////////////
//		lexer		//
//////////////////////
// syntax_error.c
int		check_inner_chars(char *word, char c);
int		syntax_error(t_token *head);

// unclosed_quotes.c
int		unclosed_quotes(char *str);

// lexer.c
t_token	*lexer(char **tokens);

// split_tokens.c
char	**split_tokens(char *pipe);

// token_types.c
void	set_types(t_token *head);

//////////////////////
//		parser		//
//////////////////////
// cmds.c
t_cmd	*parser(t_token *head);

// env_expand.c
char	*ft_clean_quotes(char *word);
t_token	*env_expand(t_token *head);

//////////////////////
//		uitls		//
//////////////////////
// print.c
void	print_str_array(char **arr);
void	print_tokens(t_token *head);
void	print_cmds(t_cmd *head);

// str_utils.c
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strcat(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);

// utils.c
int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
int		ft_is_space(char c);
void	ft_reverse_str(char *str, int len);
void	ft_itoa(int n, char *str);

//////////////////////////////////////////
//			Under Construction			//
//////////////////////////////////////////
int		exec_cmds(t_cmd *cmd_list);
char	**ft_split(const char *s, char c);

#endif
