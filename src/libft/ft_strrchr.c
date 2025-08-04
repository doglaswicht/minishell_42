/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:52:35 by pedroribeir       #+#    #+#             */
/*   Updated: 2024/11/11 00:16:02 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	ptr = s;
	while (*ptr != '\0')
		ptr++;
	while (ptr != s - 1)
	{
		if (*ptr == (char)c)
			return ((char *)ptr);
		ptr--;
	}
	return (NULL);
}
