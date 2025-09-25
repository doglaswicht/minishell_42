/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:43 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 14:31:12 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "redir.h"
#include "signals.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	child_process_exec(t_cmd *cmd, t_shell *shell, int is_last)
{
	int	status;

	(void)is_last;
	if (handle_redirections(cmd, shell) < 0)
	{
		shell->last_exit_code = 1;
		if (g_signal == 130)
			shell->last_exit_code = 130;
		exit(shell->last_exit_code);
	}
	if (is_builtin(cmd))
	{
		status = execute_builtin(cmd, shell);
		exit(status);
	}
	exit(launch_execve(cmd, shell));
}

int	spawn_child_process(t_cmd *cmd, t_shell *shell, int *fds, int is_last)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		handle_exec_error("fork");
		return (-1);
	}
	if (pid == 0)
	{
		reset_signals();
		if (fds[0] != STDIN_FILENO)
			dup2(fds[0], STDIN_FILENO);
		if (fds[1] != STDOUT_FILENO)
			dup2(fds[1], STDOUT_FILENO);
		close_all_pipes(shell->pipes, shell->pipe_count);
		child_process_exec(cmd, shell, is_last);
	}
	if (is_last)
		shell->last_pid = pid;
	return (pid);
}

int	launch_execve(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		ret;

	path = resolve_command_path(cmd->argv[0], shell->env);
	envp = env_to_str_array(shell->env);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]);
		free_envp(envp);
		return (127);
	}
	execve(path, cmd->argv, envp);
	ret = errno;
	handle_exec_error(cmd->argv[0]);
	free(path);
	free_envp(envp);
	if (ret == EACCES)
		return (126);
	return (127);
}
