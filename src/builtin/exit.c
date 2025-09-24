/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:48 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/26 22:52:03 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>

int	count_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	return (i);
}

int	is_valid_exit_code_arg(const char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	long	code;

	printf("exit\n");
	if (cmd->argv[1])
	{
		if (!is_valid_exit_code_arg(cmd->argv[1]))
		{
			printf("exit: %s: numeric argument required\n", cmd->argv[1]);
			shell->last_exit_code = 2;
			shell->is_running = 0;
			return (2);
		}
		if (count_args(cmd) > 2)
		{
			printf("exit: too many arguments\n");
			shell->last_exit_code = 1;
			return (1);
		}
		code = ft_atol(cmd->argv[1]);
		shell->last_exit_code = (int)(code & 255);
		shell->is_running = 0;
		return (shell->last_exit_code);
	}
	shell->is_running = 0;
	return (shell->last_exit_code);
}
