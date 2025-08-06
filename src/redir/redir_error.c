/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:08:50 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 01:08:52 by dleite-b         ###   ########.fr       */
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