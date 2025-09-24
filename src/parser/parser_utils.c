/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:27:50 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/08/26 23:14:28 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cleanup.h"
#include "libft.h"
#include <stdlib.h>

void	free_command_list(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_command(cmds);
		cmds = tmp;
	}
}

size_t	count_argv_len(char **argv)
{
	size_t	len;

	len = 0;
	while (argv && argv[len])
		len++;
	return (len);
}

char	**allocate_new_argv(size_t len)
{
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (len + 2));
	return (new_argv);
}

void	copy_argv(char **new_argv, char **argv)
{
	size_t	i;

	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
}

void	free_old_argv(char **argv)
{
	size_t	i;

	if (argv)
	{
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
}
