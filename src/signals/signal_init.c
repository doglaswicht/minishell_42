#include "signals.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	// rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
