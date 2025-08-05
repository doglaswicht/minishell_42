#include "quotes.h"

int quotes_balanced(const char *line)
{
    int i;
    int quote;

    if (!line)
        return (1);
    i = 0;
    quote = 0;
    while (line[i])
    {
        if (!quote && is_quote(line[i]))
            quote = line[i];
        else if (quote && line[i] == quote)
            quote = 0;
        i++;
    }
    return (quote == 0);
}

int contains_unclosed_quotes(const char *s)
{
    if (!s)
        return (0);
    return (!quotes_balanced(s));
}

int is_quoted_segment(const char *s, int i)
{
    int idx;
    int quote;

    if (!s || i < 0)
        return (0);
    idx = 0;
    quote = 0;
    while (s[idx] && idx < i)
    {
        if (!quote && is_quote(s[idx]))
            quote = s[idx];
        else if (quote && s[idx] == quote)
            quote = 0;
        idx++;
    }
    return (quote != 0);
}