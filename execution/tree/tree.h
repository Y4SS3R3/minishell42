/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:20:39 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/07 12:47:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../../minishell.h"

typedef struct s_token	t_token;
typedef struct s_trash	t_trash;
typedef struct s_shell	t_shell;

typedef struct s_redir
{
	char			*file;
	char			*type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*previous;
	struct s_token	*right;
	struct s_token	*left;
	char			*cmd;
	char			**args;
	int				nature;
	char			*in;
	char			*out;
	int				fd_in;
	int				fd_out;
	t_redir			*redirs_out;
	t_redir			*redirs_in;
}	t_token;

typedef struct s_tree
{
	t_token			*info;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

t_token	*token_clone(t_token *token);
t_token	*ft_lstnew(char *cmd);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *pre);
size_t	ft_strcmp(char *s1, char *s2);
void	print_stack(t_token *stack);
void	print_stack_s(t_token *stack);
void	*ft_free(char **to_free, size_t elements, int flag);
t_token	*ft_tree(t_token **control, t_shell *data);
void	print2D(t_token *root);
t_redir	*last_redir(t_redir *head);
t_redir	*token_to_redir(t_token *token);
void	append_redir(t_redir **head, t_redir *new);
t_redir	*redir(t_token **input, int check1, int check2);

#endif
