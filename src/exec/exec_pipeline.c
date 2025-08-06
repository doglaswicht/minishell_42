/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:47 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:48 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>

int	**g_pipes = NULL;
int	g_pipe_count = 0;

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

static int	setup_pipeline_execution(t_cmd *cmds)
{
	g_pipe_count = setup_pipes(cmds, &g_pipes);
	if (g_pipe_count < 0)
		return (-1);
	return (0);
}

static int	execute_pipeline_commands(t_cmd *cmds, t_shell *shell)
{
	int		i;
	int		fds[2];
	t_cmd	*tmp;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		fds[0] = (i == 0) ? STDIN_FILENO : g_pipes[i - 1][0];
		fds[1] = (i == g_pipe_count) ? STDOUT_FILENO : g_pipes[i][1];
		if (spawn_child_process(tmp, shell, fds, i == g_pipe_count) < 0)
		{
			close_all_pipes(g_pipes, g_pipe_count);
			free_pipe_fds(g_pipes, g_pipe_count);
			return (-1);
		}
		tmp = tmp->next;
		i++;
	}
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
	if (setup_pipeline_execution(cmds) < 0)
		return (1);
	if (execute_pipeline_commands(cmds, shell) < 0)
		return (1);
	close_all_pipes(g_pipes, g_pipe_count);
	shell->last_exit_code = wait_for_all(cmds);
	free_pipe_fds(g_pipes, g_pipe_count);
	g_pipes = NULL;
	g_pipe_count = 0;
	return (shell->last_exit_code);
}
