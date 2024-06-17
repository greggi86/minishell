/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:01:16 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/12 15:31:10 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_BUILTINS_H
# define M_BUILTINS_H

# include "minishell.h"

typedef int				(*t_builtin_func)(char *cmd, t_data *data);

typedef struct s_builtin
{
	char			*cmd;
	t_builtin_func	func;
} t_builtin

static const s_builtin g_builtin[] = {

	{"echo", m_echo},
	{"cd", m_cd},
	{"pwd", m_pwd},
	{"export", m_export},
	{"unset", m_unset},
	{"env", m_env},
	{"exit", m_exit},
	{0}
}	t_builtin;

#endif // BUILTIN.H