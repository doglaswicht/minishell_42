/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:13:32 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:26:13 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "env.h"
# include "utils.h"

typedef struct s_expand_ctx
{
	t_env	*env;
	int		last_status;
	int		quote;
	int		i;
}	t_expand_ctx;

char	*expand_variables(const char *line, t_env *env, int last_status);
char	*expand_loop(const char *line, t_expand_ctx *ctx);

char	*append_char(char *str, char c);
char	*handle_exit_status(const char *line, int *i, int last_status);
char	*handle_variable_expansion(const char *line, int *i, t_env *env);
char	*process_dollar_sign(const char *line, int *i, t_env *env,
			int last_status);
char	*handle_quote_case(char *result, const char *line, int *i, int *q);
char	*handle_dollar_case(char *result, const char *line, t_expand_ctx *ctx);

char	*expand_var_token(const char *token, t_env *env);
char	*expand_exit_status(const char *line, int status);
int		is_expandable(char c);
char	*extract_var_key(const char *line, int *len);
char	*expand_env_value(const char *key, t_env *env);
char	*get_env_value(t_env *env, const char *key);

#endif
