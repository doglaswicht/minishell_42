/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:17:51 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:48:34 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_prompt_state
{
        PROMPT_DEFAULT,
        PROMPT_HEREDOC
}       t_prompt_state;

void            init_prompt(void);
void            set_prompt_state(t_prompt_state state);
t_prompt_state  get_prompt_state(void);
void            set_last_status(int status);
int             get_last_status(void);
char            *read_user_input(void);
void            display_prompt(void);
void            free_user_input(char *line);
int             is_interactive_shell(void);
void            init_readline(void);

#endif