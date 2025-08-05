/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:50 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:51 by dleite-b         ###   ########.fr       */
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
int open_output_file(const char *filename, int append)
{
    int flags;
    int fd;

    flags = O_WRONLY | O_CREAT;
    if (append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(filename, flags, 0644);
    if (fd < 0)
        perror(filename);
    return (fd);
}

/*
** setup_redir_output
** ------------------------------------------------------------
** Handles output related redirections ('>' and '>>').  The
** appropriate file is opened and duplicated onto STDOUT.  The
** temporary file descriptor is closed before returning.  Returns
** 0 on success or -1 on failure.
*/
int setup_redir_output(t_redir *redir)
{
    int fd;

    if (redir->type == TOKEN_REDIR_OUT)
        fd = open_output_file(redir->target, 0);
    else if (redir->type == TOKEN_REDIR_APPEND)
        fd = open_output_file(redir->target, 1);
    else
        return (0);
    if (fd < 0)
        return (-1);
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}