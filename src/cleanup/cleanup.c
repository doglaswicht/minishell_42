/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:20:07 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/08/05 16:51:54 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include <stdlib.h>


void    free_redirections(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->target);
        free(redir);
        redir = tmp;
    }
}

void    free_command(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->argv)
        free_split(cmd->argv);
    if (cmd->redir)
        free_redirections(cmd->redir);
    free(cmd);
}

void    free_shell(t_shell *shell)
{
    if (!shell)
        return;
    if (shell->env)
        free_env_list(shell->env);
}

void    deep_cleanup_on_error(t_shell *shell)
{
    exit_clean(shell, EXIT_FAILURE);
}