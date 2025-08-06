/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:55 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 15:36:32 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include "libft.h"

/*
** free_split
** ---------------------------------------------------------------------------
** Wrapper around libft's ft_free_split to centralise freeing logic.
*/
void	free_split(char **arr)
{
	ft_free_split(arr);
}
