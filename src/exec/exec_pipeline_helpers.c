/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:27:45 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:28:36 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>

void	setup_fds(int fds[2], int i, t_shell *shell)
{
	if (i == 0)
		fds[0] = STDIN_FILENO;
	else
		fds[0] = shell->pipes[i - 1][0];
	if (i == shell->pipe_count)
		fds[1] = STDOUT_FILENO;
	else
		fds[1] = shell->pipes[i][1];
}

int	execute_single_command_in_pipeline(t_cmd *cmd, t_shell *shell,
		int fds[2], int is_last)
{
	if (spawn_child_process(cmd, shell, fds, is_last) < 0)
	{
		close_all_pipes(shell->pipes, shell->pipe_count);
		free_pipe_fds(shell->pipes, shell->pipe_count);
		return (-1);
	}
	return (0);
}

int	execute_pipeline_commands(t_cmd *cmds, t_shell *shell)
{
	int		i;
	int		fds[2];
	t_cmd	*tmp;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		setup_fds(fds, i, shell);
		if (execute_single_command_in_pipeline(tmp, shell, fds,
				i == shell->pipe_count) < 0)
			return (-1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
