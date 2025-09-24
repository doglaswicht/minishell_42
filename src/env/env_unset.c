/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:35 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:46:10 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static int	remove_env_node(t_env **env, t_env *cur, t_env *prev)
{
	if (prev)
		prev->next = cur->next;
	else
		*env = cur->next;
	free_env_node(cur);
	return (0);
}

int	unset_env_value(t_env **env, const char *key)
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
			return (remove_env_node(env, cur, prev));
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
