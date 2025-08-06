/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:55:13 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:55:14 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Count how many command segments exist in the list of tokens
** Segments are separated by PIPE tokens. Returns 0 for empty list
*/

int	count_command_segments(t_token *tokens)
{
	int	count;

	if (!tokens)
		return (0);
	count = 1;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

/*
** Check if tokens contain at least one pipe
*/

int	command_needs_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/*
** Determine if a command structure has no arguments and no redirections
*/

int	command_is_empty(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	if ((!cmd->argv || !cmd->argv[0]) && cmd->redir == NULL)
		return (1);
	return (0);
}

/*
** Verify whether a token represents a redirection operator
*/

int	is_redirection_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}