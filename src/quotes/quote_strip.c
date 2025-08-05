/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_strip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:26 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:27 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "libft.h"
#include "utils.h"

char    *remove_quotes(const char *str)
{
    char    *out;
    size_t  i;
    size_t  j;
    int     quote;

    if (!str)
        return (NULL);
    out = safe_malloc(ft_strlen(str) + 1);
    i = 0;
    j = 0;
    quote = 0;
    while (str[i])
    {
        if (!quote && is_quote(str[i]))
            quote = str[i];
        else if (quote && str[i] == quote)
            quote = 0;
        else
            out[j++] = str[i];
        i++;
    }
    out[j] = '\0';
    return (out);
}
