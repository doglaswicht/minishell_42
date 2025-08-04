/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:12:24 by procha-r          #+#    #+#             */
/*   Updated: 2025/05/26 20:14:19 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include <sys/wait.h>

typedef struct s_cmd		t_cmd;
typedef struct s_shell		t_shell;

typedef struct s_io_backup
{
	int	stdin_fd;
	int	stdout_fd;
}	t_io_backup;

int		execute_pipeline(t_cmd *cmds, t_shell *shell);
int		execute_single_command(t_cmd *cmd, t_shell *shell);
int		spawn_child_process(t_cmd *cmd, t_shell *shell, int *fds, int is_last);
void	child_process_exec(t_cmd *cmd, t_shell *shell, int is_last);
char	*resolve_command_path(char *cmd, t_env *env);
int		is_path_absolute_or_relative(const char *cmd);
int		is_valid_executable(const char *path);
int		launch_execve(t_cmd *cmd, t_shell *shell);
void	handle_exec_error(const char *msg);
int		setup_pipes(t_cmd *cmds, int ***pipes);
void	close_all_pipes(int **pipes, int count);
void	free_pipe_fds(int **pipes, int count);
int		wait_for_all(t_cmd *cmds);
void	update_exit_code_from_status(int status);

#endif
