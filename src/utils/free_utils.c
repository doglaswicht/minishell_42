#include "cleanup.h"
#include "libft.h"

/*
** free_split
** ---------------------------------------------------------------------------
** Wrapper around libft's ft_free_split to centralise freeing logic.
*/
void    free_split(char **arr)
{
    ft_free_split(arr);
}