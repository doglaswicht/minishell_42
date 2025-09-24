/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:45:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:44:47 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	is_valid_env_key(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	env_key_exists(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& env->key[ft_strlen(key)] == '\0')
			return (1);
		env = env->next;
	}
	return (0);
}

char	*create_env_string(t_env *tmp)
{
	char	*key_eq;
	char	*result;

	key_eq = ft_strjoin(tmp->key, "=");
	if (!key_eq)
		return (NULL);
	result = ft_strjoin(key_eq, tmp->value);
	free(key_eq);
	return (result);
}

size_t	count_env_nodes(t_env *env)
{
	size_t	count;

	count = 0;
	while (env && ++count)
		env = env->next;
	return (count);
}

int	fill_env_array(char **arr, t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		arr[i] = create_env_string(env);
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (0);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (1);
}
