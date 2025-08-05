#include "input.h"
#include <unistd.h>

static t_prompt_state  g_prompt_state = PROMPT_DEFAULT;

t_prompt_state  get_prompt_state(void)
{
        return (g_prompt_state);
}

void    set_prompt_state(t_prompt_state state)
{
        g_prompt_state = state;
}

int     is_interactive_shell(void)
{
        return (isatty(STDIN_FILENO));
}

void    display_prompt(void)
{
        if (!is_interactive_shell())
                return ;
        if (g_prompt_state == PROMPT_HEREDOC)
                write(STDOUT_FILENO, "> ", 2);
        else
                write(STDOUT_FILENO, " minishell$ ", 12);
}

void    free_user_input(char *line)
{
        if (line)
                free(line);
}