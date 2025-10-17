/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:54:50 by procha-r          #+#    #+#             */
/*   Updated: 2025/10/18 00:28:56 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

char	*get_target_path(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv[1])
		return (cmd->argv[1]);
	return (get_env_value(shell->env, "HOME"));
}

int	handle_cd_error(char *oldpwd)
{
	perror("cd");
	free(oldpwd);
	return (1);
}

void	update_env_dirs(t_shell *shell, char *oldpwd, char *cwd)
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
