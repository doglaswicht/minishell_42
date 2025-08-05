/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:10:09 by procha-r          #+#    #+#             */
/*   Updated: 2025/06/06 12:30:16 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include <unistd.h>
# include "parser.h"
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

int             handle_redirections(t_cmd *cmd);
int             redir_apply(t_redir *redir);
int             setup_redir_input(t_redir *redir);
int             open_input_file(const char *filename);
int             setup_redir_output(t_redir *redir);
int             open_output_file(const char *filename, int append);
int             heredoc(const char *delimiter);
void    close_redirections(t_cmd *cmd);
void    apply_redirections(t_cmd *cmd);
int             handle_redir_error(const char *msg);

#endif
