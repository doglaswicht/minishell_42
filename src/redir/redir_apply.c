/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:42 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 13:50:20 by procha-r         ###   ########.fr       */
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
int	redir_apply(t_redir *redir, t_shell *shell)
{
	if (!redir)
		return (0);
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		return (setup_redir_input(redir, shell));
	if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APPEND)
		return (setup_redir_output(redir, shell));
	return (-1);
}
