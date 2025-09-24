/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:13:21 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/26 23:15:48 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cleanup.h"
#include "libft.h"
#include <stdlib.h>

void	ft_add_arg(char ***argv, const char *value)
{
	size_t	len;
	char	**new_argv;

	if (!value)
		return ;
	len = count_argv_len(*argv);
	new_argv = allocate_new_argv(len);
	if (!new_argv)
		return ;
	copy_argv(new_argv, *argv);
	new_argv[len] = ft_strdup(value);
	new_argv[len + 1] = NULL;
	free_old_argv(*argv);
	*argv = new_argv;
}
