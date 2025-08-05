#include "signals.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

/*
** Handlers para sinais no processo pai e processo filho.
*/

void    signal_handler_parent(int sig)
{
    if (sig == SIGINT)
    {
        set_signal_code(130);
        rl_on_new_line();
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
    {
        set_signal_code(131);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    signal_handler_child(int sig)
{
    if (sig == SIGINT)
    {
        set_signal_code(130);
        write(1, "\n", 1);
    }
    else if (sig == SIGQUIT)
    {
        set_signal_code(131);
        write(1, "Quit (core dumped)\n", 19);
    }
}