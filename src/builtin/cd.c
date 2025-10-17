/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:31 by dleite-b          #+#    #+#             */
/*   Updated: 2025/10/18 00:29:05 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target;
	char	*oldpwd;
	char	*cwd;

	if (cmd->argv && cmd->argv[1] && cmd->argv[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
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
