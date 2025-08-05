/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:59 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:00 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

/*
** expand_env_value
** ---------------------------------------------------------------------------
** Retrieves the value of the given environment variable key from the `env`
** list.  If the key does not exist an empty string is returned.  The returned
** string is dynamically allocated and must be freed by the caller.
*/
char    *expand_env_value(const char *key, t_env *env)
{
    char    *value;

    if (!key)
        return (safe_strdup(""));
    value = get_env_value(env, key);
    if (!value)
        return (safe_strdup(""));
    return (safe_strdup(value));
}

/*
** expand_var_token
** ---------------------------------------------------------------------------
** Expands a token that represents a variable (e.g. "$HOME").  If the token
** does not start with '$' it is duplicated as-is.  The returned string is
** dynamically allocated and must be freed by the caller.
*/
char    *expand_var_token(const char *token, t_env *env)
{
    char    *key;
    char    *value;
    int     len;

    if (!token)
        return (NULL);
    if (token[0] != '$')
        return (safe_strdup(token));
    key = extract_var_key(token + 1, &len);
    value = expand_env_value(key, env);
    free(key);
    return (value);
}