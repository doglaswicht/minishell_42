/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:17:51 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/26 23:23:34 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redir.h"
#include "quotes.h"
#include "libft.h"
#include <stdlib.h>

t_redir	*new_redirection(t_token_type type, const char *target)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = ft_strdup(target);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_redirection(t_redir **list, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!list || !new_redir)
		return ;
	if (!*list)
	{
		*list = new_redir;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

int	process_word_token(t_cmd *current, t_token *token)
{
	char	*clean;

	if (current)
	{
		clean = remove_quotes(token->value);
		ft_add_arg(&current->argv, clean);
		free(clean);
	}
	return (0);
}

int	process_redirection_token(t_cmd *current, t_token **tokens)
{
	t_redir	*redir;

	if (!current || !(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		return (-1);
	redir = new_redirection((*tokens)->type, (*tokens)->next->value);
	if (!redir)
		return (-1);
	add_redirection(&current->redir, redir);
	*tokens = (*tokens)->next;
	return (0);
}

t_cmd	*create_new_command(t_cmd **cmds, int needs_pipe, int segment_index)
{
	t_cmd	*current;

	current = new_command();
	if (!current)
	{
		free_command_list(*cmds);
		return (NULL);
	}
	if (needs_pipe && segment_index > 0)
		current->pipe_in = 1;
	add_command(cmds, current);
	return (current);
}
