/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:09:31 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 15:19:32 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "redir.h"

/*
** open_input_file
** ------------------------------------------------------------
** Wrapper around open() for input files.  Returns the file
** descriptor on success or -1 on failure.
*/
int	open_input_file(const char *filename)
{
	if (!filename)
		return (-1);
	return (open(filename, O_RDONLY));
}

/*
** setup_redir_input
** ------------------------------------------------------------
** Handles input related redirections ("<" and heredoc).  It
** obtains the appropriate file descriptor and duplicates it onto
** STDIN.  The original descriptor is closed afterwards.  Returns
** 0 on success or -1 on failure.
*/
int	setup_redir_input(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->target)
		return (handle_redir_error("redirection"));
	if (redir->type == TOKEN_REDIR_IN)
		fd = open_input_file(redir->target);
	else if (redir->type == TOKEN_HEREDOC)
		fd = heredoc(redir->target);
	else
		return (0);
	if (fd < 0)
		return (handle_redir_error(redir->target));
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (handle_redir_error("dup2"));
	}
	close(fd);
	return (0);
}
