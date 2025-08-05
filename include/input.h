/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:17:51 by procha-r          #+#    #+#             */
/*   Updated: 2025/05/26 20:24:13 by procha-r         ###   ########.fr       */
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

void            set_prompt_state(t_prompt_state state);
t_prompt_state  get_prompt_state(void);
char            *read_user_input(void);
void            display_prompt(void);
void            free_user_input(char *line);
int                     is_interactive_shell(void);
void            init_readline(void);

#endif