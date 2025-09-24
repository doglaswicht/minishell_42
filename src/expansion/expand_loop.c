/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:22:23 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:24:40 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

char	*expand_loop(const char *line, t_expand_ctx *ctx)
{
	char	*result;

	result = safe_strdup("");
	ctx->i = 0;
	ctx->quote = 0;
	while (line[ctx->i])
	{
		if (line[ctx->i] == '\'' || line[ctx->i] == '"')
			result = handle_quote_case(result, line, &ctx->i, &ctx->quote);
		else if (line[ctx->i] == '$' && ctx->quote != '\'')
			result = handle_dollar_case(result, line, ctx);
		else
			result = append_char(result, line[ctx->i++]);
	}
	return (result);
}
