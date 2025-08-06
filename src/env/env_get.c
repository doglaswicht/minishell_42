/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:30 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 13:19:57 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

char	*get_env_value(t_env *env, const char *key)
{
	size_t	klen;

	if (!env || !key)
		return (NULL);
	klen = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, klen) == 0 && env->key[klen] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_has_key(t_env *env, const char *key)
{
	size_t	klen;

	if (!env || !key)
		return (0);
	klen = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, klen) == 0 && env->key[klen] == '\0')
			return (1);
		env = env->next;
	}
	return (0);
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
