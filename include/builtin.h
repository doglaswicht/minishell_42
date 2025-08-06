/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:11:49 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/06 12:15:32 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "env.h"
# include "parser.h"

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef int		(*t_builtin_fn)(t_cmd *cmd, t_shell *shell);

int						is_builtin(t_cmd *cmd);
int						execute_builtin(t_cmd *cmd, t_shell *shell);

int						builtin_echo(t_cmd *cmd);
int						check_echo_flag(char *arg);
int						builtin_cd(t_cmd *cmd, t_shell *shell);
int						update_pwd(t_shell *shell);
int						update_oldpwd(t_shell *shell);
int						change_dir(const char *path, t_shell *shell);
int						builtin_pwd(void);
int						builtin_env(t_cmd *cmd, t_env *env);
int						builtin_export(t_cmd *cmd, t_shell *shell);
int						validate_export_argument(const char *s);
int						export_variable(const char *arg, t_shell *shell);
void					sort_and_print_env(t_env *env);
void					export_print_sorted(t_env *env);
int						builtin_unset(t_cmd *cmd, t_shell *shell);
int						builtin_exit(t_cmd *cmd, t_shell *shell);
int						is_valid_exit_code_arg(const char *arg);
int						count_args(t_cmd *cmd);

#endif
