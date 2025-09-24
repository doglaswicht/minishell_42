/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:47 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 18:28:10 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>

static int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static int	setup_pipeline_execution(t_cmd *cmds, t_shell *shell)
{
	shell->pipe_count = setup_pipes(cmds, &shell->pipes);
	if (shell->pipe_count < 0)
		return (-1);
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int	cmd_count;

	if (!cmds)
		return (0);
	cmd_count = count_cmds(cmds);
	if (cmd_count == 1)
		return (execute_single_command(cmds, shell));
	if (setup_pipeline_execution(cmds, shell) < 0)
		return (1);
	if (execute_pipeline_commands(cmds, shell) < 0)
		return (1);
	close_all_pipes(shell->pipes, shell->pipe_count);
	shell->last_exit_code = wait_for_all(cmds, shell);
	free_pipe_fds(shell->pipes, shell->pipe_count);
	shell->pipes = NULL;
	shell->pipe_count = 0;
	return (shell->last_exit_code);
}
