/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:42 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:43 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
** redir_apply
** ------------------------------------------------------------
** Dispatch function that chooses the correct handler for the
** given redirection node based on its type.  Returns 0 on success
** or -1 if the setup function reports an error or the type is
** unknown.
*/
int redir_apply(t_redir *redir)
{
    if (!redir)
        return (0);
    if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
        return (setup_redir_input(redir));
    if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APPEND)
        return (setup_redir_output(redir));
    return (-1);
}
