/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:15:18 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/07/24 00:28:02 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_REDIR_APPEND 4
# define TOKEN_HEREDOC 5
# define TOKEN_AND_IF 6
# define TOKEN_OR_IF 7
# define TOKEN_UNKNOWN 999

void	free_token_list(t_token *head)
{
	(void)head;
}