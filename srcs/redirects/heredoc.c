/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:43:35 by grbuchne          #+#    #+#             */
/*   Updated: 2024/06/25 19:01:29 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_LINE_LEN 1024
#define MAX_HEREDOCS 100

ssize_t ft_readlines(int fd, char *buffer, ssize_t maxlen)
{
    ssize_t n = 0;
    ssize_t bytes_read;
    char c;

    if (!buffer || maxlen == 0)
        return -1;

    while ((bytes_read = read(fd, &c, 1)) > 0)
    {
        if (n < maxlen - 1)
        {
            buffer[n++] = c;
            if (c == '\n')
                break;
        }
        else
            break;
    }

    if (bytes_read < 0)
        return -1;
    else if (bytes_read == 0 && n == 0)
        return 0;
    else
        buffer[n] = '\0';

    return n;
}


void cleanup_heredocs(t_cmd *cmd)
{
    for (int i = 0; i < cmd->heredoc_count; i++)
    {
        free(cmd->heredocs[i].filename);
        free(cmd->heredocs[i].delimiter);
        unlink(cmd->heredocs[i].filename);
    }
    free(cmd->heredocs);
    cmd->heredocs = NULL;
    cmd->heredoc_count = 0;
}

t_token *create_token(const char *word, t_token_type type) {
    t_token *token = malloc(sizeof(t_token));
    token->word = strdup(word);
    token->type = type;
    token->prev = NULL;
    token->next = NULL;
    return token;
}

int process_single_heredoc(const char *delimiter, const char *filename)
{
    char line[MAX_LINE_LEN];
    int tmp_fd;
    ssize_t len;

    tmp_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (tmp_fd < 0)
    {
        perror("open");
        return -1;
    }

    while (1)
    {
        len = ft_readlines(STDIN_FILENO, line, sizeof(line));
        if (len < 0)
        {
            perror("ft_readlines");
            close(tmp_fd);
            return -1;
        }
        if (len == 0) // EOF
            break;

        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }

        if (strcmp(line, delimiter) == 0)
        {
            break;
        }

        strcat(line, "\n");
        len++;

        if (write(tmp_fd, line, len) == -1)
        {
            perror("write");
            close(tmp_fd);
            return -1;
        }
    }

    close(tmp_fd);
    return 0;
}

int process_all_heredocs(t_doc *heredocs, int heredoc_count)
{
    for (int i = 0; i < heredoc_count; i++)
    {
        if (process_single_heredoc(heredocs[i].delimiter, heredocs[i].filename) != 0)
        {
            fprintf(stderr, "Failed to process heredoc %d\n", i + 1);       //->putstrfd()
            return -1;
        }
    }

    for (int i = 0; i < heredoc_count; i++)
    {
        int tmp_fd = open(heredocs[i].filename, O_RDONLY);
        if (tmp_fd != -1)
        {
            char buffer[MAX_LINE_LEN];
            ssize_t len;
            while ((len = read(tmp_fd, buffer, sizeof(buffer))) > 0)
            {
                write(STDOUT_FILENO, buffer, len);
            }
            close(tmp_fd);
        }
    }

    return 0;
}

int check_heredoc(t_token *token_list, t_cmd *cmd)
{
    t_token *current = token_list;
    t_doc heredocs[MAX_HEREDOCS];
    int heredoc_count = 0;
    char filename[20];

    while (current != NULL)
    {
        if (current->type == HEREDOC && current->next != NULL)
        {
            if (heredoc_count >= MAX_HEREDOCS)
            {
                fprintf(stderr, "Too many heredocs\n");         //->putstrfd()
                return -1;
            }

            snprintf(filename, sizeof(filename), "/tmp/heredoc_%d", heredoc_count);
            heredocs[heredoc_count].filename = strdup(filename);
            heredocs[heredoc_count].delimiter = strdup(current->next->word);

            free(current->word);
            current->word = strdup(filename);
            current->type = INPUT;

            // Remove the delimiter token
            t_token *temp = current->next;
            current->next = temp->next;
            if (temp->next)
                temp->next->prev = current;
            free(temp->word);
            free(temp);

            heredoc_count++;
        }
        current = current->next;
    }

    cmd->heredocs = (t_doc *)malloc(sizeof(t_doc) * heredoc_count);
    if (cmd->heredocs == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for heredocs\n");        //->putstrfd()
        return -1;
    }
    memcpy(cmd->heredocs, heredocs, sizeof(t_doc) * heredoc_count);
    cmd->heredoc_count = heredoc_count;

    return 0;
}

int main() {
    t_token *token_list = create_token("cat", WORD);
    token_list->next = create_token("<<", HEREDOC);
    token_list->next->prev = token_list;
    token_list->next->next = create_token("EOF1", WORD);
    token_list->next->next->prev = token_list->next;
    token_list->next->next->next = create_token("<<", HEREDOC);
    token_list->next->next->next->prev = token_list->next->next;
    token_list->next->next->next->next = create_token("EOF2", WORD);
    token_list->next->next->next->next->prev = token_list->next->next->next;

    t_cmd cmd = {0};

    if (check_heredoc(token_list, &cmd) != 0) {
        fprintf(stderr, "Failed to handle heredocs\n");     //->putstrfd()
    
        return 1;
    }

    if (process_all_heredocs(cmd.heredocs, cmd.heredoc_count) != 0)
    {
    fprintf(stderr, "Failed to process heredocs\n");        //->putstrfd()
    cleanup_heredocs(&cmd);
    return (1);
    }
    cleanup_heredocs(&cmd);
    // Free token list
    return 0;
}