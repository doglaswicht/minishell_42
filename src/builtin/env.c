#include "builtin.h"

int     builtin_env(t_cmd *cmd, t_env *env)
{
    (void)cmd;
    print_env_list(env);
    return (0);
}