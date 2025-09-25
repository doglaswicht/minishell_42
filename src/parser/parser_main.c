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

#define STATE_NEEDS_PIPE 0
#define STATE_SEGMENT_INDEX 1
#define STATE_TOTAL_SEGMENTS 2

static void	handle_pipe_token(t_cmd ***current, int state[3])
{
	if (**current && !command_is_empty(**current)
		&& state[STATE_NEEDS_PIPE]
		&& state[STATE_SEGMENT_INDEX] < state[STATE_TOTAL_SEGMENTS] - 1)
		(**current)->pipe_out = 1;
	**current = NULL;
	state[STATE_SEGMENT_INDEX]++;
}

static int	create_command_if_needed(
		t_token *token,
		t_cmd ***current,
		t_cmd **cmds,
		int state[3])
{
	int	needs;
	int	segment;

	if (**current || token->type == TOKEN_PIPE)
		return (1);
	needs = state[STATE_NEEDS_PIPE];
	segment = state[STATE_SEGMENT_INDEX];
	**current = create_new_command(cmds, needs, segment);
	if (!**current)
		return (0);
	return (1);
}

static int	process_redirection_node(
		t_cmd *current,
		t_token **tokens,
		t_cmd **cmds)
{
	if (!current)
		return (1);
	if (process_redirection_token(current, tokens) == -1)
	{
		free_command_list(*cmds);
		return (0);
	}
	return (1);
}

static t_cmd	*parse_token_loop(
		t_token *tokens,
		t_cmd **cmds,
		t_cmd **current,
		int state[3])
{
	while (tokens)
	{
		if (!create_command_if_needed(tokens, &current, cmds, state))
			return (NULL);
		if (tokens->type == TOKEN_WORD)
			process_word_token(*current, tokens);
		else if (is_redirection_token(tokens))
		{
			if (!process_redirection_node(*current, &tokens, cmds))
				return (NULL);
		}
		else if (tokens->type == TOKEN_PIPE)
			handle_pipe_token(&current, state);
		tokens = tokens->next;
	}
	return (*cmds);
}

t_cmd	*parse_tokens_to_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;
	int		state[3];

	cmds = NULL;
	current = NULL;
	state[STATE_NEEDS_PIPE] = command_needs_pipe(tokens);
	state[STATE_SEGMENT_INDEX] = 0;
	state[STATE_TOTAL_SEGMENTS] = count_command_segments(tokens);
	return (parse_token_loop(tokens, &cmds, &current, state));
}
