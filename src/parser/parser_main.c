/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:27:37 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/06/06 18:29:49 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

static t_cmd	*new_command_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_command_node(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*parse_tokens_to_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current)
		{
			current = new_command_node();
			if (!current)
				return (NULL);
			add_command_node(&cmds, current);
		}
		if (tokens->type == TOKEN_WORD)
			ft_add_arg(&current->argv, tokens->value);
		else if (tokens->type == TOKEN_PIPE)
			current = NULL;
		tokens = tokens->next;
	}
	return (cmds);
}