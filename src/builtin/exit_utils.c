/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/02/14 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <limits.h>

static int	accumulate_digit(
		unsigned long long *uvalue,
		char c,
		int sign)
{
	*uvalue = *uvalue * 10 + (c - '0');
	if ((sign == 1 && *uvalue > (unsigned long long)LLONG_MAX)
		|| (sign == -1
			&& *uvalue > (unsigned long long)LLONG_MAX + 1ULL))
		return (0);
	return (1);
}

int	count_args(t_cmd *cmd)
{
	int	index;

	index = 0;
	while (cmd->argv && cmd->argv[index])
		index++;
	return (index);
}

int	is_valid_exit_code_arg(const char *arg)
{
	int	index;

	if (!arg)
		return (0);
	index = 0;
	if (arg[index] == '+' || arg[index] == '-')
		index++;
	if (!arg[index])
		return (0);
	while (arg[index])
	{
		if (!ft_isdigit(arg[index]))
			return (0);
		index++;
	}
	return (1);
}

int	parse_exit_value(const char *arg, long long *value)
{
	unsigned long long	uvalue;
	int					sign;
	size_t				idx;

	uvalue = 0;
	sign = 1;
	idx = 0;
	if (arg[idx] == '+' || arg[idx] == '-')
	{
		if (arg[idx] == '-')
			sign = -1;
		idx++;
	}
	while (arg[idx])
	{
		if (!accumulate_digit(&uvalue, arg[idx], sign))
			return (0);
		idx++;
	}
	if (sign == -1)
		*value = -(long long)uvalue;
	else
		*value = (long long)uvalue;
	return (1);
}
