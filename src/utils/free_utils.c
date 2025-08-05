#include "cleanup.h"
#include <stdlib.h>

/*
** free_split
** ---------------------------------------------------------------------------
** Frees a NULL-terminated array of strings and the array itself.  This is a
** small wrapper used throughout the project to centralise freeing logic.
*/
void free_split(char **arr)
{
    int i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}