/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_char_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:23:48 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:23:57 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

char	*append_char(char *str, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strndup(buf, 1);
	str = ft_strjoin_free(str, tmp);
	free(tmp);
	return (str);
}

char	*handle_quote_case(char *result, const char *line, int *i, int *q)
{
	if (!*q)
		*q = line[*i];
	else if (*q == line[*i])
		*q = 0;
	result = append_char(result, line[*i]);
	(*i)++;
	return (result);
}
