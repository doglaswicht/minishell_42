#include "signals.h"

static int g_signal_code = 0;

void    set_signal_code(int code)
{
    g_signal_code = code;
}

int     get_signal_code(void)
{
    return (g_signal_code);
}