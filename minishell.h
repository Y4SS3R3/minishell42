/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:41:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/05/15 21:44:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include "./execution/tree/tree.h"
# include "./execution/gc/gc.h"
# include "./execution/exec/exec.h"
# include "./parsing/mahmoud.h"

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	OPEN_PAR = '(',
	CLOSE_PAR = ')',
	STAR = '*',
	AND,
	OR,
	HERE_DOC,
	APPEND,
};

# define READ 0
# define WRITE 1

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

typedef struct s_trash
{
	void			*to_free;
	struct s_trash	*next;
}	t_trash;

typedef struct s_shell
{
	int		in_par;
	int		def_in;
	int		def_out;
	int		to_close;
	int		status;
	int		index;
	char	**envp;
	char	**paths;
	t_token	*the_tree;
	t_trash	*gc;
}	t_shell;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*s;
	int 			nature;
    int				quote;
	int				d_quote;
}

void	putstr_fd(char *msg, int fd);
void	lst_free(t_token *head);
int		get_length(char **array);
void	infix_to_postfix(t_token *infix,
			t_token **exp, t_token **stack, t_shell *data);
char	*check_command(char *command, char **paths);
void	dup2_plus(int old, int new, t_shell *data);
void	error_protocole(char *msg, t_shell *data, int exit_s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	check_env(t_shell *data, char **env);
char	**ft_split(char const *s, char c);
void	check_potential_path(t_shell *data);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *haystack, int needle);
int		pipe_line(t_token *token, t_shell *data);
void	dfs_tree(t_token *root, t_shell *data);
int		exec_child(t_token *token, t_shell *data);
void	update_status(t_shell *data);
void	and_handler(t_token *token, t_shell *data);
void	or_handler(t_token *token, t_shell *data);
void	ft_exec(t_token *token, t_shell *data);
void	exec_tind(t_token *root, t_shell *data);
t_trash	*gc_last(t_trash *head);
void	gc_add(t_trash **head, t_trash *new);
t_trash	*gc_new(void *address);
void	*malloc_plus(size_t size, t_shell *data);
void	gc_free(t_shell *data);
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
