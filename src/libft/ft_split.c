/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:01:04 by pedroribeir       #+#    #+#             */
/*   Updated: 2024/11/11 03:08:08 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*copy_word(const char *s, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_words(char **words, int i)
{
	while (i > 0)
	{
		free(words[i - 1]);
		i--;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		len;

	words = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words || !s)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			words[i] = copy_word(s, len);
			if (!words[i++])
				return (free_words(words, i - 1), NULL);
			s += len;
		}
		else
			s++;
	}
	words[i] = NULL;
	return (words);
}
