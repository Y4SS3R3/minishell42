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
# include <dirent.h>
# include <limits.h>
# include <sys/wait.h>
# include <termios.h>

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
	AND = 76,
	OR = 248,
	HERE_DOC,
	APPEND,
};

# define READ 0
# define WRITE 1
# define GLOBAL 13
# define LOOP 37
# define CTRLC_HRDC -13
# define MALLOC_FAILURE 3
# define GCFAILED_ERRMSG "Cannot open minishell : garbage collector failure\n"
# define GCAPPEND_ERRMSG "Warning: Appending newly allocated address failed\n"

typedef struct s_token	t_token;
typedef struct s_trash	t_trash;
typedef struct s_shell	t_shell;
typedef struct s_redir	t_redir;
typedef struct s_tree	t_tree;
typedef struct s_list	t_list;

int						g_sig;

typedef struct s_replace_info
{
	char	*result;
	size_t	res_i;
	size_t	i;
	size_t	rem_len;
	int		first_occurrence;
}	t_replace_info;

typedef struct s_attrr
{
	char	*key;
	char	*key2;
	int		index;
}	t_attrr;

typedef struct s_info
{
	char	*final;
	int		j;
	int		i;
}	t_info;

typedef struct s_arr
{
	char	**old_arr;
	char	**new_arr;
	int		index;
}	t_arr;

typedef struct s_sub
{
	char			*s;
	unsigned int	start;
	size_t			len;
}	t_sub;

typedef struct s_fd
{
	int			fd;
	int			visited;
	int			ex_flag;
	char		*file_name;
	char		*limiter;
	struct s_fd	*next;
}	t_fd;

typedef struct s_redir
{
	char			*file;
	char			*type;
	t_fd			*hdc;
	int				ambiguos;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*previous;
	struct s_token	*right;
	struct s_token	*left;
	int				quote;
	int				d_quote;
	int				par;
	char			*cmd;
	char			*key_q;
	char			*key_d_q;
	int				join;
	char			**args;
	int				nature;
	char			*in;
	char			*out;
	int				fd_in;
	int				fd_out;
	t_fd			*hdc;
	t_redir			*after;
	t_redir			*before;
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
	int				freed;
	struct s_trash	*next;
}	t_trash;

typedef struct s_shell
{
	int				fork;
	int				add_equal;
	int				cd_flag;
	int				to_close;
	int				exapp;
	int				free_it;
	int				unlink_it;
	char			*key;
	char			*key2;
	char			*key3;
	int				status;
	int				exec;
	int				show_err;
	int				rem1;
	int				rem2;
	int				errno_shell;
	char			**envp;
	char			*saved_path;
	char			*last_arg;
	char			*fildes;
	t_list			*envl;
	char			**paths;
	t_token			*the_tree;
	t_trash			*g_gc;
	t_trash			*l_gc;
	t_fd			*fds;
	struct termios	orig_termios;
}	t_shell;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*s;
	char			*key_q;
	char			*key_d_q;
	int				nature;
	int				quote;
	int				hide;
	int				d_quote;
}	t_list;

void	putstr_fd(char *msg, int fd);
char	*mz_strdup(const char *s1, t_shell *data);
int		get_length(char **array);
char	*check_command(char *command, char **paths, t_shell *data);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, int mode, t_shell *data);
void	check_env(t_shell *data);
char	**ft_split(char *s, char c, int mode, t_shell *data);
void	check_potential_path(t_shell *data);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *haystack, int needle);
void	pipe_line(t_token *token, t_shell *data);
void	dfs_tree(t_token *root, t_shell *data);
int		exec_child(t_token *token, t_shell *data);
void	update_status(t_shell *data);
void	and_handler(t_token *token, t_shell *data);
void	or_handler(t_token *token, t_shell *data);
void	ft_exec(t_token *token, t_shell *data);
void	exec_tind(t_token *root, t_shell *data);
t_trash	*gc_last(t_trash *head);
void	gc_add(t_trash **head, t_trash *new);
void	*malloc_p(size_t size, t_trash *gc, t_shell *data);
void	gc_free(t_shell *data, int mode);
t_token	*token_clone(t_token *token, t_shell *data);
t_token	*ft_lstnew(char *cmd, int mode, t_shell *data);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new, t_token *pre);
size_t	ft_strcmp(char *s1, char *s2);
void	print_stack(t_token *stack);
void	print_stack_s(t_token *stack);
void	*ft_free(char **to_free, size_t elements, int flag);
t_token	*ft_tree(t_token **control, t_shell *data);
void	print2D(t_token *root);
t_redir	*last_redir(t_redir *head);
t_redir	*token_to_redir(t_token *token, t_shell *data);
void	append_redir(t_redir **head, t_redir *new);
t_redir	*redir(t_token **input, t_shell *data);
char	*ft_strdup(const char *s1, int mode, t_shell *data);
char	*ft_substr_s(t_sub *info, int mode, t_shell *data);
t_list	*mz_lstnew(char *content, int mode, t_shell *data);
void	mz_lstadd_back(t_list **lst, t_list *new);
t_list	*mz_lstlast(t_list *lst);
t_list	*env_parse(char **envp, t_shell *data);
t_token	*mz_parser(char *s, int *status, t_shell *data);
int		mz_is_space(char c);
int		mz_is_special(char c);
int		make_word_nd(t_list **head, char *s, int i, t_shell *data);
int		make_out(t_list **head, char *s, int i, t_shell *data);
int		make_quote(t_list **head, char *s, int i, t_shell *data);
int		make_dquote(t_list **head, char *s, int i, t_shell *data);
int		make_dollar(t_list **head, char *s, int i, t_shell *data);
int		make_star(t_list **head, char *s, int i, t_shell *data);
void	mz_make_special(t_token **list, t_list **head, t_shell *data);
char	*ft_itoa(int n, int mode, t_shell *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		cd(int ac, char **av, t_shell *data);
int		pwd(t_shell *data);
int		execute_builtin(t_token *token, t_shell *data);
int		is_a_builtin(t_token *node);
char	**update_arg(char *book, char **shelf);
void	print_2d_array(char **arr);
int		echo(int ac, char **av);
int		env(t_shell *data);
int		ft_atoi(char *str);
int		exit_cmd(int ac, char **av, t_shell *data);
void	remove_token(t_list **head, t_list *to_remove);
int		unset(int ac, char **av, t_shell *data);
int		export(int ac, char **av, t_shell *data);
int		handle_redirs(t_redir *in, t_shell *data, int dup_it);
void	cmd_or_bltin(t_token *root, t_shell *data);
void	mz_splitter(t_token *head, t_shell *data);
char	**mz_nul_split(char const *s, char c, int n);
void	search_remove(t_list **haystack, char *needle, t_shell *data);
char	*get_var_name(char *var, t_shell *data);
char	**list_to_arr(t_list *head, t_shell *data);
char	*search_fetch_add(char **env, char *to_find, t_shell *data);
int		open_out(t_redir *out, t_shell *data);
int		open_in(t_redir *in, t_shell *data);
int		is_a_redir(t_token *root);
int		heredocing_time(t_shell *data, char **file);
int		heredocing_time_cmd(t_shell *data, char **file, t_redir *heredoc);
t_list	*search_fetch_list(t_list *head, char *to_find, t_shell *data);
void	update_var(char *val, char *name, t_list *node, t_shell *data);
int		ft_tolower(int c);
size_t	ft_strcmp_b(char *s1, char *s2);
char	*get_var_value(char *name, t_shell *data);
int		mz_search(char *s, int i, char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_expand(t_token *node, t_shell *data);
int		ex_checkredirs(t_token *node, t_shell *data);
void	ex_checkargs(t_token *node, t_shell *data);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**ws_split(char *str, t_shell *data);
char	*mz_joiner(char *s);
t_fd	*generate_heredoc(t_token *infix, t_shell *data);
void	print_fds(t_fd *head);
char	*randomize_file_name(t_shell *data);
t_fd	*fds_last(t_fd *head);
char	*get_next_line(int fd, t_shell *data);
int		ex_heredoc(t_fd *node, char **new_file, t_shell *data);
char	*mz_strjoin(char const *s1, char const *s2, t_shell *data);
size_t	mz_strlen(const char *s);
int		mz_strchr(const char *s, char c);
size_t	mz_strlcpy(char *dst, char *src, size_t dstsize);
char	*ex_key_2_assign(char *s, char *key_s, t_shell *data);
char	*ex_assign(char *str, char *flag, t_shell *data);
char	*remove_quotes(char *input, t_shell *data);
char	**ym_arr_in(t_arr *info, int *size, t_shell *data);
char	**ym_arr_rem(char **array, int index, int *size, t_shell *data);
void	free_list(t_list *head);
int		keep_quotes(char *str);
void	print_list(t_list *head);
void	append_to_env(char *name, char *value, int flag, t_shell *data);
void	free_token(t_token *head);
void	free_trash(t_trash *head);
void	free_fds(t_fd *head);
void	assign_hdc(t_fd *fds, t_token *infix);
t_fd	*fds_new(t_shell *data);
t_fd	*fds_last(t_fd *lst);
void	fds_addback(t_fd **head, t_fd *new);
int		heredoc(char *limiter, t_fd *node, t_shell *data);
void	update_shlvl(t_shell *data);
t_trash	*init_shell(t_shell *data, char **env);
void	init_shell_1(t_shell *data);
t_trash	*init_l_gc(t_shell *data);
void	init_path(t_shell *data);
char	*prompt_user(t_shell *data);
int		prompt_manage(t_shell *data, char *rl);
void	free_programm(t_shell *data);
void	free_command(t_shell *data, char *line);
char	*append_fdes(t_shell *data, int new);
void	close_fildes(t_shell *data);
int		check_var(char *input, char **name, t_shell *data);
int		ft_star(t_token *node, t_shell *data);
int		check_ambiguos(char *file);
void	ctrl_c(int sig);
void	ctrl_c_heredoc(int sig);
void	ctrl_d(t_shell *data);
void	update_pwd(char *currpwd, t_shell *data);
char	*join_chdir(char *currpwd, char *path, t_shell *data);
void	cd_custompath(char *currpwd, char *path, t_shell *data);
t_trash	*gc_new(void *address, t_shell *data);
void	handle_builtin(t_token *root, t_shell *data);
int		redirs(t_token *root, t_shell *data);
int		expand(t_token *root, t_shell *data);
int		ft_isdigit(int c);
int		get_len(char *str, char *milestone);
char	*ex_assign(char *input, char *flag, t_shell *data);
void	cpy_remain(char **input, char **final, t_shell *data);
void	cpy_incr(char **input, char **tmp, char **final, t_shell *data);
int		extract_name(char **input, char **tmp, char **name, t_shell *data);
void	join_remain(char **input, char **tmp, char **final, t_shell *data);
void	ex_remove_quotes(t_token *node, t_shell *data);
void	ex_checkcmd(t_token *node, t_shell *data);
char	*ws_strdup(char *src, int len, t_shell *data);
int		ex_words_count(const char *s);
int		ex_mz_valid(char c, int *flag);
int		ex_mz_next_word(t_info *info, char *s, char *key);
int		ex_mz_next_q(t_info *info, char *s, char *key, int flag);
void	ex_mz_key_insert(t_info *info, char *s, char *key);
int		ex_mz_size_count(char *s, char *key_s);
char	**ym_arr_rem(char **array, int index, int *size, t_shell *data);
char	*remove_ws(char *str, t_shell *data);
void	alpha_sort(char **arr, int size);
int		match_it(char *string, char *pattern);
void	star_checkcmd(t_token *node, t_shell *data);
void	star_checkargs(t_token *node, t_shell *data);
char	*get_entry_content(char *pattern, t_shell *data);
int		star_checkredirs(t_token *node, t_shell *data);
t_list	*ym_lstnew(char *content, int mode, t_shell *data);
void	ym_lstadd_back(t_list **lst, t_list *new);
t_list	*ym_lstlast(t_list *lst);
void	*which_malloc(int mode, size_t size, t_shell *data);
int		words_count(const char *s, char c);
char	*replace_key(char *original, char *to_remove, t_shell *data);
int		redir_in(t_redir *in, t_shell *data);
int		heredoc_in(t_shell *data, int *flag, char **file, t_redir *node);
int		check_empty_str(char *file, t_shell *data);
void	check_ifdir(t_token *token);
char	*fill_heredoc(char *limiter, t_shell *data);
int		open_hdc(char *file, t_fd *node, t_shell *data);
int		hrdc_ctrlc(int fd, t_shell *data);
int		end_hdc(int fd, char *file, t_shell *data);
int		is_a_dir(char *path);
void	init_1(char **file, int *expanded, char *file_src);
void	print_export(t_list *envl);
int		export_var(int ac, char **av, t_shell *data);
int		parse_var(char *input, char **val, char **name, t_shell *data);
int		skip_var_name(char *input);
char	*export_get_name(int len, int k, char *input, t_shell *data);
int		export_parse_name(char *tmp);
int		check_get_len(char *input, int *i, char **val, t_shell *data);
char	*export_get_val(char *input, int k, int len, t_shell *data);
char	**mz_split(char const *s, char c, t_shell *data);
char	*ft_strjoin_mz(char const *s1, char const *s2, t_shell *data);
char	*ft_strdup_mz(const char *s1, t_shell *data);
char	*ft_substr_mz(char const *s, unsigned int start,
			size_t len, t_shell *data);
t_list	*mz_lstnew_mz(char *content, t_shell *data);
void	mz_lstadd_back(t_list **lst, t_list *new);
t_list	*mz_lstlast(t_list *lst);
int		mz_is_space(char c);
int		mz_is_special(char c);
int		make_space_nd(t_list **head, char *s, int i, t_shell *data);
int		make_special_nd(t_list **head, char *s, int i, t_shell *data);
int		make_pipe(t_list **head, char *s, int i, t_shell *data);
int		make_in(t_list **head, char *s, int i, t_shell *data);
int		make_and(t_list **head, char *s, int i, t_shell *data);
int		make_o_par(t_list **head, char *s, int i, t_shell *data);
int		make_c_par(t_list **head, char *s, int i, t_shell *data);
t_token	*mz_last_scan(t_list *head, t_shell *data);
void	mz_make_cmd(t_token **list, t_list **head, t_shell *data);
char	**mz_arr(char **org, char **arr, char *s, int flag, t_shell *data);
int		mz_syntax_handler(t_list *lst);
int		mz_search(char *s, int i, char c);
size_t	ft_strlen_mz(const char *s);
char	**mz_nl_sp(char const *s, char c, int n, t_shell *data);
void	mz_make_redi(t_token **list, t_list **head, t_shell *data);
int		mz_key_assign(char **s, t_shell *data);
void	mz_key_insert(t_info *info, char *s, char *key, char *key_half);
int		mz_flag(char c, int flag);
char	*ft_itoa_mz(int n, t_shell *data);
char	*mz_joiner(char *s);
int		mz_syntax_err(char *s);
int		mz_syntax_err2(char *s);
int		mz_check_op(t_list *lst);
int		check_before_opar(char *s);
int		check_before_special(char *s);
char	*mz_key_assign2(char *s, char *key, t_shell *data);
void	mz_free_char(char *s);
t_token	*ft_lstnew_mz(char *cmd, t_shell *data);
char	*bring_star_back(char *input, char *key, t_shell *data);
char	*trim_string(char *str, t_shell *data);
char	*remove_charindex(char *src, int i1, int i2, t_shell *data);
int		get_switch_value(int c);
char	*find_replace(char *s1, char *s2, char *s3, t_shell *data);
void	ft_strcpy(char *dst, const char *src);
void	stop_programm(t_shell *data);
void	fds_error(t_shell *data, char *msg);
void	generate_find_replace(char **to_find,
			char **replace_with, char *key, t_shell *data);
#endif
