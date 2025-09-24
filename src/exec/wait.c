/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:52 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:08:25 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/wait.h>

int	wait_for_all(t_cmd *cmds, t_shell *shell)
{
	int		count;
	int		status;
	t_cmd	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	status = 0;
	if (shell->last_pid > 0)
		waitpid(shell->last_pid, &status, 0);
	count--;
	while (count-- > 0)
		wait(NULL);
	shell->last_exit_code = update_exit_code_from_status(status);
	return (shell->last_exit_code);
}
