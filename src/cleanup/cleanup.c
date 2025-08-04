/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:20:07 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/08/04 15:21:53 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->env)
		free_env_list(shell->env);
}
