/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:01:09 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:51:57 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_UNKNOWN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token	*tokenize_input(const char *line);
t_token	*new_token(const char *value, t_token_type type);
void	add_token(t_token **list, t_token *new_token);
void	free_token_list(t_token *head);
int		is_metachar(char c);
int		is_operator(char c);
int		is_quote(char c);
int		is_space(char c);
int		is_end_of_token(char c);
int		token_type(const char *str);
int		is_word(const char *s);
void	print_tokens_debug(t_token *tokens);

#endif
