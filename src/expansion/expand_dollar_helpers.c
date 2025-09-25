/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:24:19 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:24:27 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

char	*handle_exit_status(const char *line, int *i, int last_status)
{
	char	*status;

	status = expand_exit_status(&line[*i], last_status);
	*i += 2;
	return (status);
}

char	*handle_variable_expansion(const char *line, int *i, t_env *env)
{
	int		len;
	char	*key;
	char	*value;

	key = extract_var_key(&line[*i + 1], &len);
	value = expand_env_value(key, env);
	free(key);
	*i += len + 1;
	return (value);
}

char	*process_dollar_sign(const char *line, int *i, t_env *env,
		int last_status)
{
	if (line[*i + 1] == '?')
		return (handle_exit_status(line, i, last_status));
	else if (line[*i + 1] == '!')
	{
		*i += 2;
		return (safe_strdup(""));
	}
	else if (line[*i + 1] && is_expandable(line[*i + 1]))
		return (handle_variable_expansion(line, i, env));
	if (line[*i + 1])
	{
		(*i)++;
		return (safe_strdup("$"));
	}
	(*i)++;
	return (safe_strdup("$"));
}

char	*handle_dollar_case(char *result, const char *line, t_expand_ctx *ctx)
{
	char	*expanded;

	expanded = process_dollar_sign(line, &ctx->i, ctx->env, ctx->last_status);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	return (result);
}
