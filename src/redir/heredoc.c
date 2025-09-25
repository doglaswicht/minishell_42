/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:39 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 13:20:03 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "input.h"
#include "redir.h"
#include "signals.h"

/*
** heredoc
** ------------------------------------------------------------
** Implements the here-document feature.  A pipe is created and
** the user is prompted for input until the delimiter string is
** provided.  The collected lines are written to the pipe and the
** read end of the pipe is returned so it can be used as the
** command's STDIN.  On any error the function returns -1.
*/

static char	*heredoc_read_line(t_shell *shell)
{
	char	*prompt;
	char	*line;

	set_prompt_state(shell, PROMPT_HEREDOC);
	prompt = build_prompt(shell);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	return (line);
}

static int	process_heredoc_input(
		int fd,
		char *line,
		const char *delimiter,
		int *aborted)
{
	if (!line)
	{
		if (g_signal == 130)
			*aborted = 1;
		return (0);
	}
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
	{
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

static int	finalise_heredoc(int fd, t_shell *shell, int aborted)
{
	close(fd);
	set_prompt_state(shell, PROMPT_DEFAULT);
	if (aborted)
	{
		shell->last_exit_code = 130;
		return (-1);
	}
	return (fd);
}

int	heredoc(const char *delimiter, t_shell *shell)
{
	int		fd[2];
	char	*line;
	int		aborted;

	if (pipe(fd) < 0)
		return (-1);
	aborted = 0;
	while (1)
	{
		line = heredoc_read_line(shell);
		if (!process_heredoc_input(fd[1], line, delimiter, &aborted))
			break ;
	}
	close(fd[1]);
	return (finalise_heredoc(fd[0], shell, aborted));
}
