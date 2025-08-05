/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:45 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:46 by dleite-b         ###   ########.fr       */
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
** descriptor on success or -1 on failure while printing the
** corresponding error using perror.
*/
int open_input_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        perror(filename);
    return (fd);
}

/*
** setup_redir_input
** ------------------------------------------------------------
** Handles input related redirections ("<" and heredoc).  It
** obtains the appropriate file descriptor and duplicates it onto
** STDIN.  The original descriptor is closed afterwards.  Returns
** 0 on success or -1 on failure.
*/
int setup_redir_input(t_redir *redir)
{
    int fd;

    if (redir->type == TOKEN_REDIR_IN)
        fd = open_input_file(redir->target);
    else if (redir->type == TOKEN_HEREDOC)
        fd = heredoc(redir->target);
    else
        return (0);
    if (fd < 0)
        return (-1);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}