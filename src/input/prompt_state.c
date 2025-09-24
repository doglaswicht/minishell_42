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
#include <unistd.h>

void	display_prompt(t_shell *shell)
{
	if (!shell->prompt.interactive)
		return ;
	if (shell->prompt.mode == PROMPT_HEREDOC)
		write(STDOUT_FILENO, "> ", 2);
	else
	{
		ft_putstr_fd("[", STDOUT_FILENO);
		ft_putnbr_fd(shell->prompt.last_status, STDOUT_FILENO);
		ft_putstr_fd("] minishell$ ", STDOUT_FILENO);
	}
}
