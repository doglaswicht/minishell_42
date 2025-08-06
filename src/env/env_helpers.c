/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:45:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 14:05:54 by dleite-b         ###   ########.fr       */
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

static char	*create_env_string(t_env *tmp)
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

char	**env_to_str_array(t_env *env)
{
	size_t	count;
	size_t	i;
	char	**arr;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = create_env_string(tmp);
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}
