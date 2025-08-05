#include "parser.h"
#include <stdlib.h>

// Allocate and initialize a new command structure
// Returns NULL on allocation failure
// The command is initialized with empty argv and redirection list
// pipe flags and builtin flag are set to 0

t_cmd   *new_command(void)
{
    t_cmd   *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redir = NULL;
    cmd->pipe_in = 0;
    cmd->pipe_out = 0;
    cmd->is_builtin = 0;
    cmd->next = NULL;
    return (cmd);
}

// Append a command to the end of the command list
// If the list pointer is NULL, the new command becomes the head

void    add_command(t_cmd **cmds, t_cmd *new_cmd)
{
    t_cmd   *tmp;

    if (!cmds || !new_cmd)
        return ;
    if (!*cmds)
    {
        *cmds = new_cmd;
        return ;
    }
    tmp = *cmds;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_cmd;
}