/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:31 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 15:50:02 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static char	*get_target_path(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv[1])
		return (cmd->argv[1]);
	return (get_env_value(shell->env, "HOME"));
}

static int	handle_cd_error(char *oldpwd)
{
	perror("cd");
	free(oldpwd);
	return (1);
}

static void	update_env_dirs(t_shell *shell, char *oldpwd, char *cwd)
{
	if (oldpwd)
	{
		set_env_value(&shell->env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (cwd)
	{
		set_env_value(&shell->env, "PWD", cwd);
		free(cwd);
	}
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target;
	char	*oldpwd;
	char	*cwd;

	target = get_target_path(cmd, shell);
	if (!target)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
		return (handle_cd_error(oldpwd));
	cwd = getcwd(NULL, 0);
	update_env_dirs(shell, oldpwd, cwd);
	return (0);
}

int	update_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	set_env_value(&shell->env, "PWD", cwd);
	free(cwd);
	return (0);
}

int	update_oldpwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	set_env_value(&shell->env, "OLDPWD", cwd);
	free(cwd);
	return (0);
}

int	change_dir(const char *path, t_shell *shell)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
	{
		set_env_value(&shell->env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	update_pwd(shell);
	return (0);
}