#include "signals.h"
#include <termios.h>
#include <unistd.h>

void    disable_echoctl(void)
{
    struct termios    term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return ;
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    enable_echoctl(void)
{
    struct termios    term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return ;
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}