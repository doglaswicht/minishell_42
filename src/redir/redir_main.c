#include "redir.h"

/*
** handle_redirections
** ------------------------------------------------------------
** Iterate over the linked list of redirections attached to a
** command and apply each one.  If any redirection fails the
** function stops processing and returns -1 so the caller can
** handle the error appropriately.  On success it returns 0.
*/
int handle_redirections(t_cmd *cmd)
{
    t_redir *current;

    if (!cmd || !cmd->redir)
        return (0);
    current = cmd->redir;
    while (current)
    {
        if (redir_apply(current) < 0)
            return (-1);
        current = current->next;
    }
    return (0);
}