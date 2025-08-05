#include "exec.h"
#include <stdio.h>

void    handle_exec_error(const char *msg)
{
    if (msg)
        perror(msg);
}