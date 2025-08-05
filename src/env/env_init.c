/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:31 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:32 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*init_env_from_environ(char **envp)
{
	t_env	*env;
	char	*sep;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		sep = ft_strchr(*envp, '=');
		if (sep)
		{
			key = ft_substr(*envp, 0, sep - *envp);
			value = ft_strdup(sep + 1);
			add_env_node(key, value, &env);
			free(key);
			free(value);
		}
		envp++;
	}
	return (env);
}
