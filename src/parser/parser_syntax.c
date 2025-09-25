/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:00 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:00:00 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static const char	*token_repr(t_token *token)
{
	if (!token || token->type == TOKEN_EOF)
		return ("newline");
	if (token->value && *token->value)
		return (token->value);
	if (token->type == TOKEN_PIPE)
		return ("|");
	if (token->type == TOKEN_REDIR_IN)
		return ("<");
	if (token->type == TOKEN_REDIR_OUT)
		return (">");
	if (token->type == TOKEN_REDIR_APPEND)
		return (">>");
	if (token->type == TOKEN_HEREDOC)
		return ("<<");
	return ("newline");
}

static void	report_syntax_error(t_shell *shell, t_token *token)
{
	const char	*repr;

	repr = token_repr(token);
	write(STDERR_FILENO,
		"minishell: syntax error near unexpected token `",
		ft_strlen("minishell: syntax error near unexpected token `"));
	write(STDERR_FILENO, repr, ft_strlen(repr));
	write(STDERR_FILENO, "'\n", 2);
	shell->last_exit_code = 2;
}

static int	check_pipe(t_token *token, t_token *prev, t_shell *shell)
{
	if (!prev || prev->type == TOKEN_PIPE)
	{
		report_syntax_error(shell, token);
		return (0);
	}
	if (!token->next)
	{
		report_syntax_error(shell, NULL);
		return (0);
	}
	if (token->next->type == TOKEN_PIPE)
	{
		report_syntax_error(shell, token->next);
		return (0);
	}
	return (1);
}

static int	check_redirection(t_token *token, t_shell *shell)
{
	if (!token->next)
	{
		report_syntax_error(shell, NULL);
		return (0);
	}
	if (token->next->type != TOKEN_WORD)
	{
		report_syntax_error(shell, token->next);
		return (0);
	}
	return (1);
}

int	validate_token_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_AND_IF || tokens->type == TOKEN_OR_IF
			|| tokens->type == TOKEN_LPAREN
			|| tokens->type == TOKEN_RPAREN
			|| tokens->type == TOKEN_UNKNOWN)
		{
			report_syntax_error(shell, tokens);
			return (0);
		}
		if (tokens->type == TOKEN_PIPE
			&& !check_pipe(tokens, prev, shell))
			return (0);
		if (is_redirection_token(tokens)
			&& !check_redirection(tokens, shell))
			return (0);
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
