/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:51 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:23:50 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

static int	count_commands(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count - 1);
}

static int	allocate_pipes(int ***pipes, int count)
{
	int	i;

	*pipes = malloc(sizeof(int *) * count);
	if (!*pipes)
		return (-1);
	i = 0;
	while (i < count)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			free_pipe_fds(*pipes, i);
			return (-1);
		}
		if (pipe((*pipes)[i]) == -1)
		{
			free_pipe_fds(*pipes, i + 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	setup_pipes(t_cmd *cmds, int ***pipes)
{
	int	count;

	*pipes = NULL;
	count = count_commands(cmds);
	if (count <= 0)
		return (0);
	if (allocate_pipes(pipes, count) == -1)
		return (-1);
	return (count);
}

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes || count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	free_pipe_fds(int **pipes, int count)
{
	int	i;

	if (!pipes || count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}
