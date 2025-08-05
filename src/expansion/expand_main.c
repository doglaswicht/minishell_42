#include "expansion.h"
#include "libft.h"

/*
** append_char
** ---------------------------------------------------------------------------
** Helper that appends a single character to a dynamically allocated string.
*/
static char  *append_char(char *str, char c)
{
    char    buf[2];
    char    *tmp;

    buf[0] = c;
    buf[1] = '\0';
    tmp = ft_strndup(buf, 1);
    str = ft_strjoin_free(str, tmp);
    free(tmp);
    return (str);
}

/*
** expand_variables
** ---------------------------------------------------------------------------
** Expands environment variables and the special `$?` sequence within the given
** line.  Expansion does not occur inside single quotes.  The returned string is
** dynamically allocated and must be freed by the caller.
*/
char    *expand_variables(const char *line, t_env *env, int last_status)
{
    char    *result;
    int     i;
    int     quote;

    if (!line)
        return (NULL);
    result = safe_strdup("");
    i = 0;
    quote = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            if (!quote)
                quote = line[i];
            else if (quote == line[i])
                quote = 0;
            result = append_char(result, line[i++]);
        }
        else if (line[i] == '$' && quote != '\'')
        {
            if (line[i + 1] == '?')
            {
                char *status = expand_exit_status(&line[i], last_status);
                result = ft_strjoin_free(result, status);
                free(status);
                i += 2;
            }
            else if (line[i + 1] && is_expandable(line[i + 1]))
            {
                int     len;
                char    *key;
                char    *value;

                key = extract_var_key(&line[i + 1], &len);
                value = expand_env_value(key, env);
                free(key);
                result = ft_strjoin_free(result, value);
                free(value);
                i += len + 1;
            }
            else
                result = append_char(result, line[i++]);
        }
        else
            result = append_char(result, line[i++]);
    }
    return (result);
}
