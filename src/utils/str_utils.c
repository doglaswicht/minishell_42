/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:58:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 18:46:47 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <limits.h>

/*
** ft_strdup_range
** ---------------------------------------------------------------------------
** Duplicates a substring from `src` starting at index `start` (inclusive) and
** ending at index `end` (exclusive). Returns a newly allocated string or NULL
** on error or if `start` is greater than `end`.
*/
char	*ft_strdup_range(const char *src, int start, int end)
{
	char	*dup;
	int		i;
	int		len;

	if (!src || start < 0 || end < start)
		return (NULL);
	len = end - start;
	dup = safe_malloc(len + 1);
	i = 0;
	while (i < len && src[start + i])
	{
		dup[i] = src[start + i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
** count_char
** ---------------------------------------------------------------------------
** Counts the occurrences of character `c` in the given string `str`.
*/
int	count_char(const char *str, char c)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

/*
** split_len
** ---------------------------------------------------------------------------
** Returns the number of elements in a NULL-terminated array of strings.
*/
int	split_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/*
** ft_atoi_strict helpers
*/
static int	ft_parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

/*
** ft_atoi_strict
** ---------------------------------------------------------------------------
** Converts the string `str` to an integer storing the result in `out`. The
** conversion is strict: returns 0 if string contains invalid chars or overflows.
*/
int	ft_atoi_strict(const char *str, int *out)
{
	long	result;
	int		sign;
	int		i;

	if (!str || !out)
		return (0);
	i = 0;
	sign = ft_parse_sign(str, &i);
	if (!ft_isdigit((unsigned char)str[i]))
		return (0);
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && - result < INT_MIN))
			return (0);
		i++;
	}
	*out = (int)(result * sign);
	return (1);
}
