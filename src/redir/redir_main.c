/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:48 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 14:28:02 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
** handle_redirections
** ------------------------------------------------------------
** Iterate over the linked list of redirections attached to a
** command and apply each one.  If any redirection fails the
** function stops processing and returns -1 so the caller can
** handle the error appropriately.  On success it returns 0.
*/
int	handle_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;

	if (!cmd || !cmd->redir)
		return (0);
	current = cmd->redir;
	while (current)
	{
		if (redir_apply(current, shell) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
