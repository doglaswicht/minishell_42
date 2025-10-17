/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:32:45 by dleite-b          #+#    #+#             */
/*   Updated: 2025/10/18 00:32:46 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "exec.h"
#include <stdio.h>
#include <sys/stat.h>

int	is_dir_path(const char *path)
{
	struct stat	sb;

	if (!path)
		return (0);
	if (stat(path, &sb) != 0)
		return (0);
	if (S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int	check_directory_and_report(t_cmd *cmd)
{
	if (is_path_absolute_or_relative(cmd->argv[0])
		&& is_dir_path(cmd->argv[0]))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", cmd->argv[0]);
		return (126);
	}
	return (-1);
}

int	report_not_found(char **envp, char *cmd0)
{
	fprintf(stderr, "minishell: %s: command not found\n", cmd0);
	free_envp(envp);
	return (127);
}

int	map_exec_errno_and_cleanup(char **envp, char *path, char *cmd0, int ret)
{
	handle_exec_error(cmd0);
	free(path);
	free_envp(envp);
	if (ret == EACCES)
		return (126);
	return (127);
}
