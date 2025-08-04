/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:54:21 by pedroribeir       #+#    #+#             */
/*   Updated: 2024/11/11 18:04:15 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	len = count_digits(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[len] = '\0';
	while (len-- && str[len] != '-')
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
