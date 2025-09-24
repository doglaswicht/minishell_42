/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:40:53 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 15:41:25 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_to_str_array(t_env *env)
{
	char	**arr;
	size_t	count;

	count = count_env_nodes(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	if (!fill_env_array(arr, env))
		return (NULL);
	return (arr);
}
