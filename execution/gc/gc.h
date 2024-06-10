/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:58:18 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 10:19:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "../../minishell.h"

t_trash	*gc_last(t_trash *head);
void	gc_add(t_trash **head, t_trash *new);
t_trash	*gc_new(void *address);
void	*malloc_plus(size_t size, t_shell *data);
void	gc_free(t_shell *data);

#endif
