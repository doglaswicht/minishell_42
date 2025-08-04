/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:14:37 by procha-r          #+#    #+#             */
/*   Updated: 2025/07/24 00:28:57 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "parser.h"
# include "env.h"
# include "exec.h"

void	free_command(t_cmd *cmd);
void	free_command_list(t_cmd *cmd);
void	free_redirections(t_redir *redir);
void	free_env_list(t_env *env);
void	free_shell(t_shell *shell);
void    exit_clean(t_shell *shell, int code);
void	deep_cleanup_on_error(t_shell *shell);
void	free_token_list(t_token *head);
void	free_split(char **arr);

#endif
