/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:53:17 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:53:18 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include <stdlib.h>
#include <readline/history.h>

void    exit_clean(t_shell *shell, int code)
{
    if (shell)
        free_shell(shell);
    rl_clear_history();
    exit(code);
}