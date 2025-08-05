/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:15:20 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:51:56 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

char	*safe_strdup(const char *s);
void	*safe_malloc(size_t size);
void	*safe_calloc(size_t count, size_t size);
void	print_error(const char *msg);
void	print_strs(char **arr);
int		ft_atoi_strict(const char *str, int *out);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strdup_range(const char *src, int start, int end);
int		count_char(const char *str, char c);
int		split_len(char **arr);

#endif
