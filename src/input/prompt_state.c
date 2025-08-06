/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:47:27 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:47:31 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include <unistd.h>

typedef struct s_prompt_info
{
	t_prompt_state	mode;
	int				last_status;
	int				interactive;
}	t_prompt_info;

static t_prompt_info	g_prompt = {PROMPT_DEFAULT, 0, 0};

void	init_prompt(void)
{
	g_prompt.mode = PROMPT_DEFAULT;
	g_prompt.last_status = 0;
	g_prompt.interactive = isatty(STDIN_FILENO);
}

t_prompt_state	get_prompt_state(void)
{
	return (g_prompt.mode);
}

void	set_prompt_state(t_prompt_state state)
{
	g_prompt.mode = state;
}

void	set_last_status(int status)
{
	g_prompt.last_status = status;
}

int	get_last_status(void)
{
	return (g_prompt.last_status);
}

int	is_interactive_shell(void)
{
	return (g_prompt.interactive);
}

void	display_prompt(void)
{
	if (!g_prompt.interactive)
		return ;
	if (g_prompt.mode == PROMPT_HEREDOC)
		write(STDOUT_FILENO, "> ", 2);
	else
	{
		ft_putstr_fd("[", STDOUT_FILENO);
		ft_putnbr_fd(g_prompt.last_status, STDOUT_FILENO);
		ft_putstr_fd("] minishell$ ", STDOUT_FILENO);
	}
}

void	free_user_input(char *line)
{
	if (line)
		free(line);
}
