/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:10:09 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 15:22:35 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include <unistd.h>
# include "parser.h"

typedef struct s_shell	t_shell;

typedef struct s_redir
{
	int				type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_heredoc_state
{
	int		tmp_fd;
	char	*delimiter;
	int		pipe_fd[2];
	int		should_expand;
}	t_heredoc_state;

int		handle_redirections(t_cmd *cmd, t_shell *shell);
int		redir_apply(t_redir *redir, t_shell *shell);
int		setup_redir_input(t_redir *redir, t_shell *shell);
int		open_input_file(const char *filename);
int		setup_redir_output(t_redir *redir, t_shell *shell);
int		open_output_file(const char *filename, int append);
int		heredoc(const char *delimiter, t_shell *shell);
void	close_redirections(t_cmd *cmd);
void	apply_redirections(t_cmd *cmd);
int		handle_redir_error(const char *msg);

#endif
