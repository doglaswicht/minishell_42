/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:53 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 17:41:37 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int     validate_export_argument(const char *s)
{
    int i;

    if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
        return (0);
    i = 1;
    while (s[i] && s[i] != '=')
    {
        if (!(ft_isalnum(s[i]) || s[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

int     export_variable(const char *arg, t_shell *shell)
{
    char    *eq;
    char    *key;
    char    *value;
    int             res;

    eq = ft_strchr(arg, '=');
    if (!eq)
        return (set_env_value(&shell->env, arg, ""));
    key = ft_substr(arg, 0, eq - arg);
    value = ft_strdup(eq + 1);
    if (!key || !value)
    {
        free(key);
        free(value);
        return (1);
    }
    res = set_env_value(&shell->env, key, value);
    free(key);
    free(value);
    return (res);
}

static int  env_count(t_env *env)
{
    int count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

static void sort_env_array(t_env **arr, int size)
{
    int     i;
    int     j;
    t_env   *tmp;

    i = 0;
    while (i < size - 1)
    {
        j = i + 1;
        while (j < size)
        {
            if (ft_strncmp(arr[i]->key, arr[j]->key, ft_strlen(arr[i]->key) + 1) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    sort_and_print_env(t_env *env)
{

    int     size;
    int     i;
    t_env   **arr;

    size = env_count(env);
    arr = malloc(sizeof(t_env *) * size);
    if (!arr)
        return ;
    i = 0;
    while (env)
    {
        arr[i++] = env;
        env = env->next;
    }
    sort_env_array(arr, size);
    i = 0;
    while (i < size)
    {
        if (arr[i]->value && arr[i]->value[0] != '\0')
            printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
        else
            printf("declare -x %s\n", arr[i]->key);
        i++;
    }
    free(arr);
}

void    export_print_sorted(t_env *env)
{
    sort_and_print_env(env);
}

int     builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;
    int status;

    if (!cmd->argv[1])
    {
        sort_and_print_env(shell->env);
        return (0);
    }
    status = 0;
    i = 1;
    while (cmd->argv[i])
    {
        if (validate_export_argument(cmd->argv[i]))
        {
            if (export_variable(cmd->argv[i], shell) != 0)
                status = 1;
        }
        else
        {
            printf("export: `%s`: not a valid identifier\n", cmd->argv[i]);
            status = 1;
        }
        i++;
    }
    return (status);
}