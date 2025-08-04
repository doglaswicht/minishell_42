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