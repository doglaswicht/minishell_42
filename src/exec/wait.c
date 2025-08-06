/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:52 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:53 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

int				g_exit_code = 0;
extern pid_t	g_last_pid;

int	wait_for_all(t_cmd *cmds)
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
	if (g_last_pid > 0)
		waitpid(g_last_pid, &status, 0);
	count--;
	while (count-- > 0)
		wait(NULL);
	update_exit_code_from_status(status);
	return (g_exit_code);
}

void	update_exit_code_from_status(int status)
{
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = 128 + WTERMSIG(status);
	else
		g_exit_code = 1;
}