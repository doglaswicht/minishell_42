/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:22:03 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 18:31:11 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "redir.h"

/*
** open_output_file
** ------------------------------------------------------------
** Opens or creates a file for output redirection.  If `append`
** is non-zero the file is opened in append mode otherwise it is
** truncated.  Returns the new file descriptor or -1 on failure.
*/
int	open_output_file(const char *filename, int append)
{
	int	flags;

	if (!filename)
		return (-1);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (open(filename, flags, 0644));
}

/*
** setup_redir_output
** ------------------------------------------------------------
** Handles output related redirections ('>' and '>>').  The
** appropriate file is opened and duplicated onto STDOUT.  The
** temporary file descriptor is closed before returning.  Returns
** 0 on success or -1 on failure.
*/
int	setup_redir_output(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	if (!redir || !redir->target)
		return (handle_redir_error("redirection"));
	if (redir->type == TOKEN_REDIR_OUT)
		fd = open_output_file(redir->target, 0);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open_output_file(redir->target, 1);
	else
		return (0);
	if (fd < 0)
		return (handle_redir_error(redir->target));
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (handle_redir_error("dup2"));
	}
	close(fd);
	return (0);
}
