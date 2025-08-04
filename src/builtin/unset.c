#include "builtin.h"

int     builtin_unset(t_cmd *cmd, t_shell *shell)
{
    int i;

    i = 1;
    while (cmd->argv[i])
    {
        unset_env_value(&shell->env, cmd->argv[i]);
        i++;
    }
    return (0);
}