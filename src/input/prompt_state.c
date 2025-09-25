/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:47:27 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:26:11 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

static char	*build_status_prompt(t_shell *shell)
{
	char	*prompt;
	char	*status;

	status = ft_itoa(shell->prompt.last_status);
	if (!status)
		return (safe_strdup("minishell$ "));
	prompt = safe_strdup("[");
	if (!prompt)
	{
		free(status);
		return (safe_strdup("minishell$ "));
	}
	prompt = ft_strjoin_free(prompt, status);
	free(status);
	if (!prompt)
		return (safe_strdup("minishell$ "));
	prompt = ft_strjoin_free(prompt, "] minishell$ ");
	if (!prompt)
		return (safe_strdup("minishell$ "));
	return (prompt);
}

char	*build_prompt(t_shell *shell)
{
	if (!shell->prompt.interactive)
		return (NULL);
	if (shell->prompt.mode == PROMPT_HEREDOC)
		return (safe_strdup("heredoc> "));
	if (shell->prompt.mode == PROMPT_CONTINUATION)
		return (safe_strdup("quote> "));
	return (build_status_prompt(shell));
}
