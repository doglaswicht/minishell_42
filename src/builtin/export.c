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

static int	is_valid_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

int	validate_export_argument(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		if (!is_valid_name_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_key_value(const char *arg, char **key, char **value,
		int *append)
{
	char	*eq;

	*append = 0;
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
		if (!*key || !*value)
			return (1);
		return (0);
	}
	if (eq > arg && *(eq - 1) == '+')
	{
		*append = 1;
		*key = ft_substr(arg, 0, (eq - arg) - 1);
	}
	else
		*key = ft_substr(arg, 0, eq - arg);
	*value = ft_strdup(eq + 1);
	if (!*key || !*value)
		return (1);
	return (0);
}

int	export_variable(const char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	int		res;
	int		append;

	key = NULL;
	value = NULL;
	if (parse_key_value(arg, &key, &value, &append))
	{
		free(key);
		free(value);
		return (1);
	}
	if (append)
		res = append_env_value(&shell->env, key, value);
	else
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
			ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		i++;
	}
	return (status);
}
