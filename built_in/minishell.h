/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:08:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/12 16:24:27 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# define PATH_MAX 1024;

typedef struct s_data
{
	char	*cmd;
	int		exit;
	int		*state;
	char	*flag;
	char	**env;

}		t_data;

int	m_echo(char *cmd, t_data *data);
int	m_cd(char *cmd, t_data *data);
int	m_env(char *cmd, t_data *data);
int	m_pwd(char *cmd, t_data *data);
int	m_exit(char *cmd, t_data *data);
int	m_export(char *cmd, t_data *data);




#endif // MINISHELL_H

