/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:52:41 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:52:42 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static int  str_eq(const char *a, const char *b)
{
    return (ft_strncmp(a, b, ft_strlen(a)) == 0 && ft_strlen(a) == ft_strlen(b));
}

int     is_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);
    if (str_eq(cmd->argv[0], "echo") || str_eq(cmd->argv[0], "cd")
        || str_eq(cmd->argv[0], "pwd") || str_eq(cmd->argv[0], "env")
        || str_eq(cmd->argv[0], "export") || str_eq(cmd->argv[0], "unset")
        || str_eq(cmd->argv[0], "exit"))
        return (1);
    return (0);
}

int     execute_builtin(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (str_eq(cmd->argv[0], "echo"))
        return (builtin_echo(cmd));
    if (str_eq(cmd->argv[0], "cd"))
        return (builtin_cd(cmd, shell));
    if (str_eq(cmd->argv[0], "pwd"))
        return (builtin_pwd());
    if (str_eq(cmd->argv[0], "env"))
        return (builtin_env(cmd, shell->env));
    if (str_eq(cmd->argv[0], "export"))
        return (builtin_export(cmd, shell));
    if (str_eq(cmd->argv[0], "unset"))
        return (builtin_unset(cmd, shell));
    if (str_eq(cmd->argv[0], "exit"))
        return (builtin_exit(cmd, shell));
    return (1);
}