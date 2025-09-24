/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:35 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 13:16:44 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "input.h"
#include "libft.h"

static char	*ensure_capacity(char *line, size_t *cap, size_t current_len, size_t extra)
{
	char	*tmp;
	size_t	needed;
	size_t	new_cap;

	needed = current_len + extra;
	if (*cap > needed)
		return (line);
	new_cap = (*cap == 0) ? 64 : *cap;
	while (new_cap <= needed)
		new_cap *= 2;
	tmp = malloc(new_cap);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	if (line)
	{
		ft_memcpy(tmp, line, current_len);
		free(line);
	}
	*cap = new_cap;
	return (tmp);
}

static char	*read_non_interactive_line(void)
{
	char	*line;
	size_t	len;
	size_t	cap;
	char	c;
	ssize_t	bytes;

	line = NULL;
	len = 0;
	cap = 0;
	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes < 0)
		{
			if (errno == EINTR)
				continue ;
			free(line);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		line = ensure_capacity(line, &cap, len, 2);
		if (!line)
			return (NULL);
		line[len++] = c;
		if (c == '\n')
			break ;
	}
	if (bytes == 0 && len == 0)
	{
		free(line);
		return (NULL);
	}
	line = ensure_capacity(line, &cap, len, 1);
	if (!line)
		return (NULL);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	line[len] = '\0';
	return (line);
}

char	*read_user_input(t_shell *shell)
{
	char	*line;

	set_prompt_state(shell, PROMPT_DEFAULT);
	if (is_interactive_shell(shell))
	{
		display_prompt(shell);
		line = readline(NULL);
		if (!line)
		{
			write(1, "exit\n", 5);
			return (NULL);
		}
		return (line);
	}
	line = read_non_interactive_line();
	if (!line)
	{
		return (NULL);
	}
	return (line);
}
