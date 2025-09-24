/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:55:10 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/26 23:27:57 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redir.h"
#include "quotes.h"
#include "libft.h"
#include <stdlib.h>

static void	handle_pipe_token(t_cmd **current, int *segment_index,
		int needs_pipe, int total_segments)
{
	if (*current && !command_is_empty(*current)
		&& needs_pipe && *segment_index < total_segments - 1)
		(*current)->pipe_out = 1;
	*current = NULL;
	(*segment_index)++;
}

static t_cmd	*parse_token_loop(t_token *tokens, t_cmd **cmds,
		t_cmd **current, int needs_pipe)
{
	int	segment_index;
	int	total_segments;

	segment_index = 0;
	total_segments = count_command_segments(tokens);
	while (tokens)
	{
		if (!*current && tokens->type != TOKEN_PIPE)
		{
			*current = create_new_command(cmds, needs_pipe, segment_index);
			if (!*current)
				return (NULL);
		}
		if (tokens->type == TOKEN_WORD)
			process_word_token(*current, tokens);
		else if (is_redirection_token(tokens) && *current)
		{
			if (process_redirection_token(*current, &tokens) == -1)
				return (free_command_list(*cmds), NULL);
		}
		else if (tokens->type == TOKEN_PIPE)
			handle_pipe_token(current, &segment_index, \
needs_pipe, total_segments);
		tokens = tokens->next;
	}
	return (*cmds);
}

t_cmd	*parse_tokens_to_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	int		needs_pipe;

	cmds = NULL;
	current = NULL;
	needs_pipe = command_needs_pipe(tokens);
	return (parse_token_loop(tokens, &cmds, &current, needs_pipe));
}
