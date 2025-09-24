/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:18:16 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 10:35:57 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

int		is_quote(char c);
int		quote_type(char c);
int		quotes_balanced(const char *line);
int		contains_unclosed_quotes(const char *s);
int		is_quoted_segment(const char *s, int i);
char	*remove_quotes(const char *str);

#endif
