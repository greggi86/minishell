/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/12 18:06:06 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

int get_home(t_env **env)
{
    t_env *i = *env;
    char *path;

    while (i != NULL)
    {
        if (strcmp(i->key, "HOME") == 0)
        {
            if (chdir(i->value) == 0)
            {
                path = getcwd(NULL, 0);
                if (path)
                {
                    t_env *k = *env;
                    while (k != NULL)
                    {
                        if (strcmp(k->key, "PWD") == 0)
                        {
                            free(k->value);
                            k->value = strdup(path);
                            free(path);
                            return (0);
                        }
                        k = k->next;
                    }
                    free(path);
                }
            }
            return (1);  
        }
        i = i->next;
    }
    return (1);  
}

int get_parent_directory_index(const char *str)
{
    int i = strlen(str) - 1;
    while (i > 0 && str[i] != '/')
        i--;
    return i;
}

int get_up(t_cmd *cmd)
{
    t_env *env = cmd->env;
    while (env != NULL)
    {
        if (strcmp(env->key, "PWD") == 0)
        {
            int index = get_parent_directory_index(env->value);
            if (index > 0)
            {
                char *new_pwd = strndup(env->value, index);
                if (new_pwd)
                {
                    free(env->value);
                    env->value = new_pwd;
                    return (0);
                }
            }
            return (1);  
        }
        env = env->next;
    }
    return (1);  
}

void change_directory(t_cmd *cmd)
{
    char *old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("getcwd");
        return;
    }

    if (!cmd->args || !cmd->args[0])
    {
        if (get_home(&cmd->env) != 0)
            fprintf(stderr, "Failed to change to HOME directory\n");
    }
    else if (strcmp(cmd->args[0], "~") == 0)
    {
        if (get_home(&cmd->env) != 0)
            fprintf(stderr, "Failed to change to HOME directory\n");
    }
    else if (strcmp(cmd->args[0], "..") == 0)
    {
        if (get_up(cmd) != 0)
            fprintf(stderr, "Failed to change to parent directory\n");
    }
    else if (chdir(cmd->args[0]) != 0)
    {
        perror("chdir");
    }
    else
    {
        char *new_pwd = getcwd(NULL, 0);
        if (new_pwd)
        {
            t_env *env = cmd->env;
            while (env)
            {
                if (strcmp(env->key, "PWD") == 0)
                {
                    free(env->value);
                    env->value = new_pwd;
                    break;
                }
                env = env->next;
            }
        }
        else
        {
            perror("getcwd");
        }
    }

    t_env *env = cmd->env;
    while (env)
    {
        if (strcmp(env->key, "OLDPWD") == 0)
        {
            free(env->value);
            env->value = old_pwd;
            return;
        }
        env = env->next;
    }
    free(old_pwd);  
}