#include "exec.h"
#include <sys/stat.h>

int     is_path_absolute_or_relative(const char *cmd)
{
    return (cmd && (cmd[0] == '/' || cmd[0] == '.'));
}

int     is_valid_executable(const char *path)
{
    struct stat sb;

    if (!path)
        return (0);
    if (access(path, X_OK) != 0)
        return (0);
    if (stat(path, &sb) != 0)
        return (0);
    if (S_ISDIR(sb.st_mode))
        return (0);
    return (1);
}

char    *resolve_command_path(char *cmd, t_env *env)
{
    char    *path_env;
    char    **paths;
    char    *tmp;
    char    *candidate;
    int     i;

    if (is_path_absolute_or_relative(cmd))
    {
        if (is_valid_executable(cmd))
            return (ft_strdup(cmd));
        return (NULL);
    }
    path_env = get_env_value(env, "PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        candidate = ft_strjoin(tmp, cmd);
        free(tmp);
        if (is_valid_executable(candidate))
        {
            i = 0;
            while (paths[i])
                free(paths[i++]);
            free(paths);
            return (candidate);
        }
        free(candidate);
        i++;
    }
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
}