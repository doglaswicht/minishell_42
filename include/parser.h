/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:03:09 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:49:07 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "env.h"

typedef struct s_redir	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	int				pipe_in;
	int				pipe_out;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parse_tokens_to_cmds(t_token *tokens);
t_cmd	*new_command(void);
void	add_command(t_cmd **cmds, t_cmd *new_cmd);
void	free_command_list(t_cmd *cmds);
int		count_command_segments(t_token *tokens);
int		command_needs_pipe(t_token *tokens);
int		command_is_empty(t_cmd *cmd);
int		is_redirection_token(t_token *token);
void	ft_add_arg(char ***argv, const char *value);

#endif
