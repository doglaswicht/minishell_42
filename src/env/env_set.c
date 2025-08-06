/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:33 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 13:38:33 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	replace_value(t_env *node, const char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (1);
	free(node->value);
	node->value = new_value;
	return (0);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

int	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;

	if (!env || !key || !value)
		return (1);
	if (!is_valid_env_key(key))
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0
			&& tmp->key[ft_strlen(key)] == '\0')
			return (replace_value(tmp, value));
		tmp = tmp->next;
	}
	add_env_node((char *)key, (char *)value, env);
	return (0);
}