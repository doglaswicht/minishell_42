/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:05:33 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:51 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	
    shell.env = init_env_from_environ(envp);
    shell.last_exit_code = 0;
    shell_loop(&shell);
    exit_clean(&shell, 0);
    return (0);
}