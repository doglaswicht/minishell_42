#include <readline/readline.h>
#include <stdlib.h>
#include "input.h"

char    *read_user_input(void)
{
	char    *line;

    set_prompt_state(PROMPT_DEFAULT);
    display_prompt();
    line = readline(NULL);
    if (!line)
    {
            if (is_interactive_shell())
                    write(1, "exit\n", 5);
            return (NULL);
    }
    return (line);
}