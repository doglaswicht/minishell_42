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

static char	*ensure_capacity(
		char *line,
		size_t *cap,
		size_t current_len,
		size_t extra)
{
	char	*tmp;
	size_t	needed;
	size_t	new_cap;

	needed = current_len + extra;
	if (*cap > needed)
		return (line);
	if (*cap == 0)
		new_cap = 64;
	else
		new_cap = *cap;
	while (new_cap <= needed)
		new_cap *= 2;
	tmp = malloc(new_cap);
	if (!tmp)
		return (free(line), NULL);
	if (line)
	{
		ft_memcpy(tmp, line, current_len);
		free(line);
	}
	*cap = new_cap;
	return (tmp);
}

static int	read_stream(char **line, size_t *len, size_t *cap)
{
	char	c;
	char	*tmp;
	int		bytes;

	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes < 0 && errno == EINTR)
			continue ;
		if (bytes <= 0)
			return (bytes);
		tmp = ensure_capacity(*line, cap, *len, 2);
		if (!tmp)
		{
			*line = NULL;
			return (-1);
		}
		*line = tmp;
		(*line)[(*len)++] = c;
		if (c == '\n')
			return (1);
	}
}

static char	*read_non_interactive_line(void)
{
	char	*line;
	size_t	len;
	size_t	cap;
	int		status;

	line = NULL;
	len = 0;
	cap = 0;
	status = read_stream(&line, &len, &cap);
	if (status == -1)
		return (NULL);
	if (status == 0 && len == 0)
		return (free(line), NULL);
	if (!line)
		return (NULL);
	line = ensure_capacity(line, &cap, len, 1);
	if (!line)
		return (NULL);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	line[len] = '\0';
	return (line);
}

static char	*read_interactive(t_shell *shell)
{
	char	*line;
	char	*prompt;

	set_prompt_state(shell, PROMPT_DEFAULT);
	prompt = build_prompt(shell);
	line = readline(prompt);
	free(prompt);
	if (!line)
		write(1, "exit\n", 5);
	return (line);
}

char	*read_user_input(t_shell *shell)
{
	if (is_interactive_shell(shell))
		return (read_interactive(shell));
	return (read_non_interactive_line());
}
