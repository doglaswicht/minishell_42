/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:16:07 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/06/06 12:25:30 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	token_type(const char *str)
{
	if (str == NULL)
		return (TOKEN_UNKNOWN);
	if (str[0] == '|' && str[1] == '|')
		return (TOKEN_OR_IF);
	if (str[0] == '&' && str[1] == '&')
		return (TOKEN_AND_IF);
	if (str[0] == '<' && str[1] == '<')
		return (TOKEN_HEREDOC);
	if (str[0] == '>' && str[1] == '>')
		return (TOKEN_REDIR_APPEND);
	if (str[0] == '<')
		return (TOKEN_REDIR_IN);
	if (str[0] == '>')
		return (TOKEN_REDIR_OUT);
	if (str[0] == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}
