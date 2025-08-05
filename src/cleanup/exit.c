#include "cleanup.h"
#include <stdlib.h>
#include <readline/history.h>

void    exit_clean(t_shell *shell, int code)
{
    if (shell)
        free_shell(shell);
    rl_clear_history();
    exit(code);
}