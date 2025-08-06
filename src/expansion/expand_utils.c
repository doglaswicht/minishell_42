/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:07 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:08 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

/*
** is_expandable
** ---------------------------------------------------------------------------
** Checks if a character can start an environment variable name after the '$'
** sign.  Characters allowed are alphabetic letters, digits and the underscore
** character.  Returning 1 means the variable is expandable, 0 otherwise.
*/
int	is_expandable(char c)
{
	if (ft_isalnum((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

/*
** extract_var_key
** ---------------------------------------------------------------------------
** Given a string starting at the first character after '$', extracts the
** variable key composed of alphanumeric characters and underscores.  The
** length of the key is stored in `len` when it is not NULL.  The returned
** string is heap-allocated and should be freed by the caller.
*/
char	*extract_var_key(const char *line, int *len)
{
	int	idx;

	if (!line)
		return (NULL);
	idx = 0;
	while (line[idx] && (ft_isalnum((unsigned char)line[idx])
			|| line[idx] == '_'))
		idx++;
	if (len)
		*len = idx;
	return (ft_strndup(line, idx));
}
