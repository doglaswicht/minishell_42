/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:53 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 16:05:25 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	validate_export_argument(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	export_variable(const char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	char	*value;
	int		res;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (set_env_value(&shell->env, arg, ""));
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	res = set_env_value(&shell->env, key, value);
	free(key);
	free(value);
	return (res);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
	{
		sort_and_print_env(shell->env);
		return (0);
	}
	status = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (validate_export_argument(cmd->argv[i]))
		{
			if (export_variable(cmd->argv[i], shell) != 0)
				status = 1;
		}
		else
		{
			printf("export: `%s`: not a valid identifier\n", cmd->argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
