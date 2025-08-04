/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:09:48 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/06/06 12:09:54 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	i;

	new = (char *)malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}