#include <readline/readline.h>
#include "input.h"

void	init_readline(void)
{
    if (!is_interactive_shell())
        return ;
    rl_catch_signals = 0;
    set_prompt_state(PROMPT_DEFAULT);
}