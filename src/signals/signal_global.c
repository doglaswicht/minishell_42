/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:09 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:57:10 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static int g_signal_code = 0;

void    set_signal_code(int code)
{
    g_signal_code = code;
}

int     get_signal_code(void)
{
    return (g_signal_code);
}