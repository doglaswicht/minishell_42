#include "cleanup.h"

void exit_clean(t_shell *shell, int code)
{
    if (shell)
        free_shell(shell);
    exit(code);
}
