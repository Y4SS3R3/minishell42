
#include "../minishell.h"

int	make_pipe(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '|')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = 248;
		i = i + 2;
	}
	else
	{
		str = ft_substr_mz(s, i, 1, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '|';
		i = i + 1;
	}
	mz_lstadd_back(head, new);
	return (i);
}

int	make_in(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '>')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '>';
		i = i + 2;
	}
	else
	{
		str = ft_substr_mz(s, i, 1, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '>';
		i = i + 1;
	}
	mz_lstadd_back(head, new);
	return (i);
}

int	make_out(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '<')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '<';
		i = i + 2;
	}
	else
	{
		str = ft_substr_mz(s, i, 1, data);
		new = mz_lstnew_mz(str, data);
		new->nature = '<';
		i = i + 1;
	}
	mz_lstadd_back(head, new);
	return (i);
}

int	make_and(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;

	if (s[i + 1] == '&')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = 76;
		i = i + 2;
	}
	else
	{
		str = ft_substr_mz(s, i, 1, data);
		new = mz_lstnew_mz(str, data);
		new->nature = -1;
		i = i + 1;
	}
	mz_lstadd_back(head, new);
	return (i);
}

int	make_quote(t_list **head, char *s, int i, t_shell *data)
{
	t_list	*new;
	char	*str;
	int		tmp;

	if (s[i + 1] == '\'')
	{
		str = ft_substr_mz(s, i, 2, data);
		new = mz_lstnew_mz(str, data);
		new->nature = -1;
		tmp = i + 2;
	}
	else
	{
		tmp = mz_search(s, i, '\'');
		if (tmp == -1)
			tmp = 1;
		str = ft_substr_mz(s, i, tmp - i, data);
		new = mz_lstnew_mz(str, data);
		new->nature = -1;
	}
	mz_lstadd_back(head, new);
	return (tmp);
}
