
#include "../minishell.h"

int	make_space_nd(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;
	int		n;

	new = NULL;
	str = NULL;
	n = i;
	while (mz_is_space(s[i]) && s[i])
		i++;
	str = ft_substr_mz(s, n, i - n, data);
	new = mz_lstnew_mz(str, data);
	new->nature = 32;
	mz_lstadd_back(head, new);
	return (i);
}

int	make_word_nd(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;
	int		n;

	new = NULL;
	str = NULL;
	n = i;
	while (!mz_is_space(s[i]) && !mz_is_special(s[i]) && s[i])
		i++;
	str = ft_substr_mz(s, n, i - n, data);
	new = mz_lstnew_mz(str, data);
	new->nature = -1;
	mz_lstadd_back(head, new);
	return (i);
}

int	make_special_nd(t_list **head, char *s, int i, t_shell *data)
{
	if (s[i] == '|')
		return (make_pipe(head, s, i, data));
	else if (s[i] == '>')
		return (make_in(head, s, i, data));
	else if (s[i] == '<')
		return (make_out(head, s, i, data));
	else if (s[i] == '&')
		return (make_and(head, s, i, data));
	else if (s[i] == '\'')
		return (make_quote(head, s, i, data));
	else if (s[i] == '\"')
		return (make_dquote(head, s, i, data));
	else if (s[i] == '$')
		return (make_dollar(head, s, i, data));
	else if (s[i] == '(')
		return (make_o_par(head, s, i, data));
	else if (s[i] == ')')
		return (make_c_par(head, s, i, data));
	else if (s[i] == '*')
		return (make_star(head, s, i, data));
	return (i);
}
