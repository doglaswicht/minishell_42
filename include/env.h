/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:01:03 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 15:43:32 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*init_env_from_environ(char **envp);
char	*get_env_value(t_env *env, const char *key);
int		set_env_value(t_env **env, const char *key, const char *value);
int		unset_env_value(t_env **env, const char *key);
int		env_key_exists(t_env *env, const char *key);
int		is_valid_env_key(const char *key);
int		env_has_key(t_env *env, const char *key);
void	add_env_node(char *key, char *value, t_env **env_list);
t_env	*new_env_node(char *key, char *value);
void	free_env_list(t_env *env);
void	print_env_list(t_env *env);

char	*create_env_string(t_env *tmp);
size_t	count_env_nodes(t_env *env);
int		fill_env_array(char **arr, t_env *env);
char	**env_to_str_array(t_env *env);

#endif
