/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:27:50 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/08/06 15:10:28 by dleite-b         ###   ########.fr       */
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

static size_t	count_argv_len(char **argv)
{
	size_t	len;

	len = 0;
	while (argv && argv[len])
		len++;
	return (len);
}

static char	**allocate_new_argv(size_t len)
{
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (len + 2));
	return (new_argv);
}

static void	copy_argv(char **new_argv, char **argv)
{
	size_t	i;

	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
}

static void	free_old_argv(char **argv)
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