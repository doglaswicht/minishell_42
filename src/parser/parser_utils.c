/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:27:50 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/07/24 00:27:18 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

void	free_command_list(t_cmd *cmds)
{
	    t_cmd   *tmp;
    size_t  i;

    while (cmds)
    {
        tmp = cmds->next;
        if (cmds->argv)
        {
            i = 0;
            while (cmds->argv[i])
                free(cmds->argv[i++]);
            free(cmds->argv);
        }
        free(cmds);
        cmds = tmp;
    }
}

void	ft_add_arg(char ***argv, const char *value)
{
	size_t	len;
	char	**new_argv;
	size_t	i;

	if (!value)
		return ;
	len = 0;
	while (*argv && (*argv)[len])
		len++;
	new_argv = malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (*argv && (*argv)[i])
	{
		new_argv[i] = ft_strdup((*argv)[i]);
		i++;
	}
	new_argv[i++] = ft_strdup(value);
	new_argv[i] = NULL;
	if (*argv)
	{
		i = 0;
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
	*argv = new_argv;
}