/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:49 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:50 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>
#include <sys/stat.h>

void	handle_exec_error(const char *msg)
{
	if (msg)
		perror(msg);
}

void	expand_tilde_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*home;
	char	*tmp;

	if (!cmd || !cmd->argv)
		return ;
	home = get_env_value(shell->env, "HOME");
	if (!home)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		if (ft_strncmp(cmd->argv[i], "~", 2) == 0)
		{
			tmp = ft_strdup(home);
			if (tmp)
			{
				free(cmd->argv[i]);
				cmd->argv[i] = tmp;
			}
		}
		i++;
	}
}

void	free_envp(char **envp)
{
	int		i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

/* moved error helpers to exec_errors.c */
