/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:20:00 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:20:00 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "quotes.h"
#include "signals.h"
#include "utils.h"
#include "libft.h"
#include <readline/readline.h>

static const char	g_quote_msg[] = "minishell: unexpected EOF while "
	"looking for matching quote";

static void	reset_line(char **line, t_shell *shell, int code)
{
	if (*line)
		free(*line);
	*line = NULL;
	shell->last_exit_code = code;
}

static int	read_continuation_input(char **extra, t_shell *shell)
{
	char	*prompt;

	set_prompt_state(shell, PROMPT_CONTINUATION);
	prompt = build_prompt(shell);
	*extra = readline(prompt);
	free(prompt);
	if (*extra)
		return (1);
	if (g_signal != 130)
		print_error(g_quote_msg);
	return (0);
}

static int	append_extra_input(char **line, char *extra, t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin_free(*line, "\n");
	if (!tmp)
	{
		*line = NULL;
		free(extra);
		reset_line(line, shell, 1);
		return (0);
	}
	*line = ft_strjoin_free(tmp, extra);
	free(extra);
	if (!*line)
	{
		reset_line(line, shell, 1);
		return (0);
	}
	return (1);
}

static int	append_continuation(char **line, t_shell *shell)
{
	char	*extra;

	if (!read_continuation_input(&extra, shell))
	{
		reset_line(line, shell, 2);
		return (0);
	}
	if (!append_extra_input(line, extra, shell))
		return (0);
	return (1);
}

char	*read_complete_line(char *line, t_shell *shell)
{
	if (!line)
		return (NULL);
	while (contains_unclosed_quotes(line))
	{
		if (!is_interactive_shell(shell))
		{
			print_error(g_quote_msg);
			shell->last_exit_code = 2;
			free(line);
			return (NULL);
		}
		if (!append_continuation(&line, shell))
			return (NULL);
	}
	set_prompt_state(shell, PROMPT_DEFAULT);
	return (line);
}
