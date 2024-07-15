/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:12:15 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/18 13:18:54 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[32mminishell> \033[0m"
# define PATH_MAX 1024;

//////////////////////////
// Include dependencies //
//////////////////////////
# include <stdio.h>             // printf & readline
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
	char		*cmd;
	char		**args;
	char		**flags;
	struct s_redir	*infiles;
	struct s_redir	*outfiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	struct s_env	*env;
	int				exit;
}	t_cmd;

//////////////////////////////////
//		Function prototypes		//
//////////////////////////////////

//	utils.c
size_t	ft_strlen(const char *s);

//	str_utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *dst, const char *src, size_t n);

//	split_tokens.c
char	**split_tokens(char *input);

//	print.c
void	print_str_array(char **arr);
void	print_tokens(t_token *head);
void	print_cmds(t_cmd *head);
void print_env_list(t_env *env);

//	lexer.c
t_token	*lexer(char **tokens);

//	cleaners.c
void	free_array(char **arr);
void	free_array_and_tokens(char **arr, t_token *head);
void	free_tokens(t_token *head);
void	free_cmd(t_cmd *head);

//	syntax_error.c
int	syntax_error(t_token *head);

//	env_expand.c
t_token	*env_expand(t_token *head);

//	cmds.c
t_cmd	*parser(t_token *head);

//	exec.c
int	exec_cmds(t_cmd *cmd_list);

//	builtins/
void	m_echo(t_cmd *cmd);
void	m_cd(t_cmd *cmd);
int		m_pwd(t_cmd *cmd);
int		m_env(t_cmd *cmd);
int		m_unset(t_cmd *cmd, char *str);
int		m_exit(t_cmd *cmd);


//	str_utils2.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//	get_envp.c
int	parse_env(char **envp, t_env **env);
char	**merge_args(t_cmd *cmd);
char	*find_command(char *cmd);
void	redirect_inputs(t_cmd *cmd);
void	redirect_outputs(t_cmd *cmd);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);

int	unclosed_quotes(char *str);
int	check_inner_chars(char *word, char c);
void	set_types(t_token *head);
int	ft_is_space(char c);
char	*ft_strndup(const char *s1, size_t n);
int	ft_isalnum(int c);
char	*ft_strcat(char *dst, const char *src);
void	ft_itoa(int n, char *str);
int	process_heredoc(const char *delimiter);
void add_env_node_back(t_env **envp, char *key, char *value);
int	split_env(char *str, char **key, char **value);
void	close_pipes(int pipes[2]);


#endif
