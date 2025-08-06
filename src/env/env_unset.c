/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:35 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 13:21:35 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int     unset_env_value(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	size_t	klen;

	if (!env || !*env || !key)
		return (1);
	cur = *env;
	prev = NULL;
	klen = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, klen) == 0 && cur->key[klen] == '\0')
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
