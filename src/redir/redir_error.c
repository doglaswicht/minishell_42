/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:08:50 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/26 23:09:34 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "redir.h"

int	handle_redir_error(const char *msg)
{
	if (msg)
		perror(msg);
	return (-1);
}
