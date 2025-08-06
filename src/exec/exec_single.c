/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:30:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 14:30:00 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "redir.h"
#include <unistd.h>

extern int		g_exit_code;

static void	restore_stdio(int saved[2])
{
	if (saved[0] >= 0)
	{
		dup2(saved[0], STDIN_FILENO);
		close(saved[0]);
	}
	if (saved[1] >= 0)
	{
		dup2(saved[1], STDOUT_FILENO);
		close(saved[1]);
	}
}

static int	handle_builtin_execution(t_cmd *cmd, t_shell *shell)
{
	int		saved[2];

	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (saved[0] < 0 || saved[1] < 0 || handle_redirections(cmd) < 0)
	{
		restore_stdio(saved);
		return (shell->last_exit_code = 1);
	}
	shell->last_exit_code = execute_builtin(cmd, shell);
	restore_stdio(saved);
	return (shell->last_exit_code);
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t		pid;
	int		status;
	int		fds[2];

	if (!cmd)
		return (0);
	if (is_builtin(cmd))
		return (handle_builtin_execution(cmd, shell));
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	pid = spawn_child_process(cmd, shell, fds, 1);
	if (pid < 0)
		return (shell->last_exit_code = 1);
	waitpid(pid, &status, 0);
	update_exit_code_from_status(status);
	shell->last_exit_code = g_exit_code;
	return (shell->last_exit_code);
}
