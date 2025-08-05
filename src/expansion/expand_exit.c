#include "expansion.h"
#include "libft.h"

/*
** expand_exit_status
** ---------------------------------------------------------------------------
** Converts the numeric exit status into a string so it can replace the special
** "$?" sequence in the input.  The returned string is dynamically allocated
** and must be freed by the caller.
*/
char    *expand_exit_status(const char *line, int status)
{
    (void)line;
    return (ft_itoa(status));
}