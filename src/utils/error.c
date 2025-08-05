#include "utils.h"
#include "libft.h"

/*
** print_error
** ---------------------------------------------------------------------------
** Writes the given error message to STDERR followed by a newline.  If the
** message pointer is NULL nothing is printed.  This function does not append
** any prefix to the message, leaving formatting to the caller.
*/
void print_error(const char *msg)
{
    if (msg)
        ft_putendl_fd((char *)msg, 2);
}

/*
** print_strs
** ---------------------------------------------------------------------------
** Utility function used for debugging purposes.  Receives a NULL-terminated
** array of strings and prints each element in its own line to STDOUT.  If the
** array itself is NULL, the function simply returns without producing any
** output.
*/
void print_strs(char **arr)
{
    int index;

    if (!arr)
        return ;
    index = 0;
    while (arr[index])
    {
        ft_putendl_fd(arr[index], 1);
        index++;
    }
}