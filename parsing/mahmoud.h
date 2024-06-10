/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mahmoud.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:26:40 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:46:35 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAHMOUD_H
#define MAHMOUD_H

# include "../minishell.h"

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*s;
	int 			nature;
    int				quote;
	int				d_quote;
}					t_list;

char	**mz_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list	*mz_lstnew(char *content);
void	mz_lstadd_back(t_list **lst, t_list *new);
t_list	*mz_lstlast(t_list *lst);
t_list	*env_parse(char **envp);
t_token	*mz_parser(char *s);
int		mz_is_space(char c);
int		mz_is_special(char c);
int		make_space_nd(t_list **head, char *s, int i);
int		make_special_nd(t_list **head, char *s, int i);
int		make_word_nd(t_list **head, char *s, int i);
int		make_pipe(t_list **head, char *s, int i);
int		make_in(t_list **head, char *s, int i);
int		make_out(t_list **head, char *s, int i);
int		make_and(t_list **head, char *s, int i);
int		make_quote(t_list **head, char *s, int i);
int		make_dquote(t_list **head, char *s, int i);
int		make_dollar(t_list **head, char *s, int i);
int		make_o_par(t_list **head, char *s, int i);
int		make_c_par(t_list **head, char *s, int i);
int		make_star(t_list **head, char *s, int i);
t_token *mz_last_scan(t_list *head);
void	mz_make_special(t_token **list, t_list **head);
void	mz_make_cmd(t_token **list, t_list **head);
char	**mz_arr(char **org, char **arr, char *s, int flag);

#endif
