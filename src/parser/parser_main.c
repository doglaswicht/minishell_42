/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:55:10 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:55:11 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redir.h"
#include "libft.h"
#include <stdlib.h>


// Helpers to build redirection linked list

static t_redir  *new_redirection(t_token_type type, const char *target)
{
    t_redir *redir;

    redir = (t_redir *)malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->target = ft_strdup(target);
    if (!redir->target)
    {
        free(redir);
        return (NULL);
    }
    redir->next = NULL;
    return (redir);
}


static void     add_redirection(t_redir **list, t_redir *new_redir)
{

    t_redir *tmp;

    if (!list || !new_redir)
        return ;
    if (!*list)
    {
        *list = new_redir;
        return ;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_redir;
}

// Parse tokens into a linked list of command structures
// Supports words, pipes and redirections

 t_cmd  *parse_tokens_to_cmds(t_token *tokens)
{
    t_cmd   *cmds;
    t_cmd   *current;
    int     segment_index;
    int     total_segments;
    int     needs_pipe;

    cmds = NULL;
    current = NULL;
    segment_index = 0;
    total_segments = count_command_segments(tokens);
    needs_pipe = command_needs_pipe(tokens);
    while (tokens)
    {
        if (!current && tokens->type != TOKEN_PIPE)
        {
            current = new_command();
            if (!current)
            {
                free_command_list(cmds);
                return (NULL);
            }
            if (needs_pipe && segment_index > 0)
                current->pipe_in = 1;
            add_command(&cmds, current);
        }
        if (tokens->type == TOKEN_WORD && current)
            ft_add_arg(&current->argv, tokens->value);
        else if (is_redirection_token(tokens) && current)
        {
            if (tokens->next && tokens->next->type == TOKEN_WORD)
            {
                t_redir *redir = new_redirection(tokens->type, tokens->next->value);
                if (!redir)
                {
                    free_command_list(cmds);
                    return (NULL);
                }
                add_redirection(&current->redir, redir);
                tokens = tokens->next;
            }
        }
        else if (tokens->type == TOKEN_PIPE)
        {
            if (current && !command_is_empty(current) && needs_pipe
                && segment_index < total_segments - 1)
                current->pipe_out = 1;
            current = NULL;
            segment_index++;
        }
        tokens = tokens->next;
    }
    return (cmds);
}
