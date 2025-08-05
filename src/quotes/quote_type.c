#include "quotes.h"

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int quote_type(char c)
{
    if (c == '\'')
        return ('\'');
    if (c == '"')
        return ('"');
    return (0);
}