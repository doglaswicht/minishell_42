/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:45 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:46 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

int	is_path_absolute_or_relative(const char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (1);
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (0);
}

int	is_valid_executable(const char *path)
{
	struct stat	sb;

	if (!path)
		return (0);
	if (stat(path, &sb) != 0)
		return (0);
	if (S_ISDIR(sb.st_mode))
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*candidate;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		candidate = ft_strjoin(tmp, cmd);
		free(tmp);
		if (is_valid_executable(candidate))
		{
			ft_free_split(paths);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	return (NULL);
}

char	*resolve_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (is_path_absolute_or_relative(cmd))
	{
		if (stat(cmd, &(struct stat){0}) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	if (!result)
		ft_free_split(paths);
	return (result);
}
