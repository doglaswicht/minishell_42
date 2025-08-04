#include "builtin.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int     builtin_pwd(void)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return (0);
    }
    perror("pwd");
    return (1);
}