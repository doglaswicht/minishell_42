/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:19:31 by pedroribeir       #+#    #+#             */
/*   Updated: 2024/11/10 21:22:27 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*src_char;
	size_t		src_len;
	size_t		i;

	src_char = (const char *)src;
	src_len = ft_strlen(src_char);
	i = 0;
	if (size > 0)
	{
		while (src_char[i] && i < (size - 1))
		{
			dst[i] = src_char[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
