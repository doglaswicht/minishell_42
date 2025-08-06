/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:05 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:06 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

/*
** append_char
** ---------------------------------------------------------------------------
** Helper that appends a single character to a dynamically allocated string.
*/
static char	*append_char(char *str, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strndup(buf, 1);
	str = ft_strjoin_free(str, tmp);
	free(tmp);
	return (str);
}

static char	*handle_exit_status(const char *line, int *i, int last_status)
{
	char	*status;

	status = expand_exit_status(&line[*i], last_status);
	*i += 2;
	return (status);
}

static char	*handle_variable_expansion(const char *line, int *i, t_env *env)
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

static char	*process_dollar_sign(const char *line, int *i, t_env *env,
		int last_status)
{
	if (line[*i + 1] == '?')
		return (handle_exit_status(line, i, last_status));
	else if (line[*i + 1] && is_expandable(line[*i + 1]))
		return (handle_variable_expansion(line, i, env));
	else
	{
		(*i)++;
		return (safe_strdup("$"));
	}
}

/*
** expand_variables
** ---------------------------------------------------------------------------
** Expands environment variables and the special `$?` sequence within the given
** line.  Expansion does not occur inside single quotes.  The returned string is
** dynamically allocated and must be freed by the caller.
*/
char	*expand_variables(const char *line, t_env *env, int last_status)
{
	char	*result;
	int		i;
	int		quote;

	if (!line)
		return (NULL);
	result = safe_strdup("");
	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!quote)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
			result = append_char(result, line[i++]);
		}
		else if (line[i] == '$' && quote != '\'')
		{
			char *expanded = process_dollar_sign(line, &i, env, last_status);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
		else
			result = append_char(result, line[i++]);
	}
	return (result);
}

