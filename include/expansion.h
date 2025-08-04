/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:13:32 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/01 16:50:02 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "env.h"
# include "utils.h"

char	*expand_variables(const char *line, t_env *env, int last_status);
char	*expand_var_token(const char *token, t_env *env);
char	*expand_exit_status(const char *line, int status);
int		is_expandable(char c);
char	*extract_var_key(const char *line, int *len);
char	*expand_env_value(const char *key, t_env *env);
char	*get_env_value(t_env *env, const char *key);

#endif
