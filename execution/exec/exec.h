/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:09:17 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:34:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../minishell.h"

int		pipe_line(t_token *token, t_shell *data);
void	dfs_tree(t_token *root, t_shell *data);
int		exec_child(t_token *token, t_shell *data);
void	update_status(t_shell *data);
void	and_handler(t_token *token, t_shell *data);
void	or_handler(t_token *token, t_shell *data);
void	ft_exec(t_token *token, t_shell *data);
void	exec_tind(t_token *root, t_shell *data);

#endif
