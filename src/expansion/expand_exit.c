/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:02 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:03 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

/*
** expand_exit_status
** ---------------------------------------------------------------------------
** Converts the numeric exit status into a string so it can replace the special
** "$?" sequence in the input.  The returned string is dynamically allocated
** and must be freed by the caller.
*/
char	*expand_exit_status(const char *line, int status)
{
	(void)line;
	return (ft_itoa(status));
}
