#include "builtin.h"
#include "libft.h"

int     check_echo_flag(char *arg)
{
    int i;

    if (!arg || arg[0] != '-')
        return (0);
    i = 1;
    if (arg[i] == '\0')
        return (0);
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int     builtin_echo(t_cmd *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (cmd->argv[i] && check_echo_flag(cmd->argv[i]))
    {
        newline = 0;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}