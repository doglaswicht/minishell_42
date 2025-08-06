/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:39 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 15:16:34 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "input.h"
#include "redir.h"

/*
** heredoc
** ------------------------------------------------------------
** Implements the here-document feature.  A pipe is created and
** the user is prompted for input until the delimiter string is
** provided.  The collected lines are written to the pipe and the
** read end of the pipe is returned so it can be used as the
** command's STDIN.  On any error the function returns -1.
*/
int	heredoc(const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		set_prompt_state(PROMPT_HEREDOC);
		display_prompt();
		line = readline(NULL);
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	set_prompt_state(PROMPT_DEFAULT);
	return (fd[0]);
}
