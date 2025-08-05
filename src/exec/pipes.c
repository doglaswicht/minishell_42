#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

int setup_pipes(t_cmd *cmds, int ***pipes)
{
    int     count;
    int     i;

    *pipes = NULL;
    count = 0;
    while (cmds)
    {
        count++;
        cmds = cmds->next;
    }
    count -= 1;
    if (count <= 0)
        return (0);
    *pipes = malloc(sizeof(int *) * count);
    if (!*pipes)
        return (-1);
    i = 0;
    while (i < count)
    {
        (*pipes)[i] = malloc(sizeof(int) * 2);
        if (!(*pipes)[i])
        {
            free_pipe_fds(*pipes, i);
            return (-1);
        }
        if (pipe((*pipes)[i]) == -1)
        {
            free_pipe_fds(*pipes, i + 1);
            return (-1);
        }
        i++;
    }
    return (count);
}

void    close_all_pipes(int **pipes, int count)
{
    int i;

    if (!pipes)
        return ;
    i = 0;
    while (i < count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void    free_pipe_fds(int **pipes, int count)
{
    int i;

    if (!pipes)
        return ;
    i = 0;
    while (i < count)
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);
}