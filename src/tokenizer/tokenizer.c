/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:25:12 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/08/26 23:11:48 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

static void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

static void	handle_word_token(const char *line, int *i, t_token **head)
{
	const char	*start;
	char		*value;
	char		quote;

	start = &line[*i];
	quote = 0;
	while (line[*i] && (quote || (!is_space(line[*i]) \
&& !is_metachar(line[*i]))))
	{
		if (is_quote(line[*i]))
		{
			if (!quote)
				quote = line[*i];
			else if (quote == line[*i])
				quote = 0;
		}
		(*i)++;
	}
	value = ft_strndup(start, *i - (start - line));
	add_token(head, new_token(value, TOKEN_WORD));
}

static void	handle_metachar_token(const char *line, int *i, t_token **head)
{
	char		*value;
	int			type;

	type = token_type(&line[*i]);
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_AND_IF || type == TOKEN_OR_IF)
	{
		value = ft_strndup(&line[*i], 2);
		*i += 2;
	}
	else
	{
		value = ft_strndup(&line[*i], 1);
		(*i)++;
	}
	add_token(head, new_token(value, type));
}

t_token	*tokenize_input(const char *line)
{
	t_token	*head;
	int		i;

	if (!line)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (line[i] && !is_metachar(line[i]))
			handle_word_token(line, &i, &head);
		else if (line[i] && is_metachar(line[i]))
			handle_metachar_token(line, &i, &head);
	}
	return (head);
}
