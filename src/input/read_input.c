#include <readline/readline.h>
#include <stdlib.h>
#include "input.h"

char	*read_user_input(void)
{
	char	*line;

	line = readline(" minishell$ ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}