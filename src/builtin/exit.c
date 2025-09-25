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
#include <unistd.h>

int	parse_exit_value(const char *arg, long long *value);

static int	report_numeric_error(const char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	shell->last_exit_code = 255;
	shell->is_running = 0;
	return (shell->last_exit_code);
}

static int	handle_too_many_args(t_shell *shell)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	shell->last_exit_code = 1;
	return (1);
}

static int	handle_exit_argument(t_cmd *cmd, t_shell *shell, int argc)
{
	long long	value;

	if (!is_valid_exit_code_arg(cmd->argv[1])
		|| !parse_exit_value(cmd->argv[1], &value))
		return (report_numeric_error(cmd->argv[1], shell));
	if (argc > 2)
		return (handle_too_many_args(shell));
	shell->last_exit_code = (unsigned char)value;
	shell->is_running = 0;
	return (shell->last_exit_code);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int		argc;

	ft_putendl_fd("exit", STDOUT_FILENO);
	argc = count_args(cmd);
	if (argc > 1)
		return (handle_exit_argument(cmd, shell, argc));
	shell->is_running = 0;
	return (shell->last_exit_code);
}
