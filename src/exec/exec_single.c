/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:30:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:23:14 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "redir.h"
#include "signals.h"
#include <unistd.h>
#include <signal.h>

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
	if (saved[0] < 0 || saved[1] < 0
		|| handle_redirections(cmd, shell) < 0)
	{
		restore_stdio(saved);
		shell->last_exit_code = 1;
		if (g_signal == 130)
			shell->last_exit_code = 130;
		return (shell->last_exit_code);
	}
	shell->last_exit_code = execute_builtin(cmd, shell);
	restore_stdio(saved);
	return (shell->last_exit_code);
}

static void	update_wait_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		shell->last_exit_code = 128 + WTERMSIG(status);
	}
	else
		shell->last_exit_code = 1;
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (!cmd)
		return (0);
	if (is_builtin(cmd))
		return (handle_builtin_execution(cmd, shell));
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	pid = spawn_child_process(cmd, shell, fds, 1);
	if (pid < 0)
	{
		shell->last_exit_code = 1;
		return (1);
	}
	waitpid(pid, &status, 0);
	update_wait_status(status, shell);
	return (shell->last_exit_code);
}
