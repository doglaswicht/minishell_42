#include "signals.h"
#include <signal.h>


void    init_signals(void)
{
	disable_echoctl();
    signal(SIGINT, signal_handler_parent);
    signal(SIGQUIT, signal_handler_parent);
    set_signal_code(0);
}

void	reset_signals(void)
{
	enable_echoctl();
    signal(SIGINT, signal_handler_child);
    signal(SIGQUIT, signal_handler_child);
}
