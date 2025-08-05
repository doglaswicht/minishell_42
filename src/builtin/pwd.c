/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:00 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:01 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int     builtin_pwd(void)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return (0);
    }
    perror("pwd");
    return (1);
}