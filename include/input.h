/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:17:51 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 13:15:32 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"

void			init_prompt(t_shell *shell);
t_prompt_state	get_prompt_state(t_shell *shell);
void			set_prompt_state(t_shell *shell, t_prompt_state state);
void			set_last_status(t_shell *shell, int status);
int				get_last_status(t_shell *shell);
int				is_interactive_shell(t_shell *shell);
char			*build_prompt(t_shell *shell);
char			*read_user_input(t_shell *shell);

void			free_user_input(char *line);
void			init_readline(void);

#endif
