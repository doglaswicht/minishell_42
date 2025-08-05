/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:33 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:34 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int  replace_value(t_env *node, const char *value)
{
    char    *new_value;

    new_value = ft_strdup(value);
    if (!new_value)
        return (1);
    free(node->value);
    node->value = new_value;
    return (0);
}

t_env   *new_env_node(char *key, char *value)
{
    t_env   *node;

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

int     is_valid_env_key(const char *key)
{
    int i;

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

int     set_env_value(t_env **env, const char *key, const char *value)
{
    t_env   *tmp;

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

int     env_key_exists(t_env *env, const char *key)
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

char    **env_to_str_array(t_env *env)
{
    size_t  count;
    size_t  i;
    char    **arr;
    t_env   *tmp;

    count = 0;
    i = 0;
    tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    tmp = env;
    while (tmp)
    {
        char *key_eq = ft_strjoin(tmp->key, "=");
        arr[i] = ft_strjoin(key_eq, tmp->value);
        free(key_eq);
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