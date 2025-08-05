/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:18:16 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:52:00 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

int contains_unclosed_quotes(const char *s);
int quotes_balanced(const char *line);
char *remove_quotes(const char *str);
int is_quoted_segment(const char *s, int i);
int quote_type(char c);
int is_quote(char c);

#endif