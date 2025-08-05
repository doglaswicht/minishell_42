/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:59 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:00 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>

/*
** ft_strjoin_free
** ---------------------------------------------------------------------------
** Joins two strings returning a newly allocated string containing the
** concatenation of s1 and s2.  The first string (s1) is freed.  If either
** parameter is NULL the function behaves accordingly:
**   - if s1 is NULL, a duplicate of s2 is returned;
**   - if s2 is NULL, s1 is returned (already allocated) without modification.
*/
char *ft_strjoin_free(char *s1, char *s2)
{
    char    *joined;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (safe_strdup(s2));
    if (!s2)
        return (s1);
    joined = ft_strjoin(s1, s2);
    if (!joined)
    {
        free(s1);
        print_error("strjoin failed");
        return (NULL);
    }
    free(s1);
    return (joined);
}