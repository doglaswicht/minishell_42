/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:36 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:37 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_env_node(char *key, char *value, t_env **env_list)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env_list)
		*env_list = new;
	else
	{
		last = *env_list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}