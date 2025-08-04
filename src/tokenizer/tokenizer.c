/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:25:12 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/06/06 12:25:13 by pedroribeir      ###   ########.fr       */
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
	int			length;
	char		*value;

	start = &line[*i];
	length = 0;
	while (line[*i] && !is_space(line[*i]) && !is_metachar(line[*i]))
	{
		(*i)++;
		length++;
	}
	value = ft_strndup(start, length);
	add_token(head, new_token(value, TOKEN_WORD));
}

static void	handle_metachar_token(const char *line, int *i, t_token **head)
{
	char		*value;
	int			type;

	value = ft_strndup(&line[*i], 1);
	type = token_type(&line[*i]);
	(*i)++;
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
