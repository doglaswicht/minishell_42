/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:57 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:57:58 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>

/*
** safe_malloc
** ---------------------------------------------------------------------------
** Allocates memory of the requested size.  If the allocation fails the
** function prints an error message and terminates the program with EXIT_FAILURE.
*/
void *safe_malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        print_error("malloc failed");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

/*
** safe_calloc
** ---------------------------------------------------------------------------
** Allocates zero-initialised memory for an array.  Behaves like safe_malloc
** regarding error handling.
*/
void *safe_calloc(size_t count, size_t size)
{
    void    *ptr;

    ptr = ft_calloc(count, size);
    if (!ptr)
    {
        print_error("calloc failed");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

/*
** safe_strdup
** ---------------------------------------------------------------------------
** Duplicates a string using ft_strdup and exits on allocation failure.
*/
char *safe_strdup(const char *s)
{
    char    *dup;

    if (!s)
        return (NULL);
    dup = ft_strdup(s);
    if (!dup)
    {
        print_error("strdup failed");
        exit(EXIT_FAILURE);
    }
    return (dup);
}
