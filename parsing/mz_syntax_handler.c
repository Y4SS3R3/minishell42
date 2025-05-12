
#include "../minishell.h"

static int	mz_check_prev(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp->prev != NULL && tmp->nature == ' ')
		tmp = tmp->prev;
	if (tmp->nature != -1 && tmp->nature != '|' && tmp->nature != '<'
		&& tmp->nature != '>' && tmp->nature != '$' && tmp->nature != 32
		&& tmp->nature != '(' && tmp->nature != ')' && tmp->nature != 76)
		return (-1);
	return (0);
}

static int	mz_redir_handler(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		while (tmp && tmp->nature != '<' && tmp->nature != '>')
			tmp = tmp->next;
		if (!tmp)
			break ;
		if (mz_check_prev(tmp) == -1)
			return (-1);
		tmp = tmp->next;
		while (tmp && tmp->nature == ' ')
			tmp = tmp->next;
		if (!tmp || tmp->nature != -1)
			return (-1);
	}
	return (0);
}

static	int	mz_in_quote(t_list *lst, t_list *nd)
{
	t_list	*tmp;
	int		flag;

	tmp = lst;
	flag = 0;
	while (tmp)
	{
		flag = mz_flag(tmp->nature, flag);
		if (tmp == nd)
			return (flag);
		tmp = tmp->next;
	}
	return (flag);
}

static int	mz_pip_handler(t_list	*lst)
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		while (lst && lst->nature == ' ')
			lst = lst->next;
		if (lst && lst->nature == '|')
			return (-1);
		while (lst && (lst->nature != '|' || mz_in_quote(lst, tmp)))
			lst = lst->next;
		if (!lst)
			break ;
		lst = lst->next;
		while (lst && lst->nature == ' ')
			lst = lst->next;
		if (!lst)
			return (-1);
	}
	return (0);
}

int	mz_syntax_handler(t_list *lst)
{
	if (mz_pip_handler(lst) || mz_redir_handler(lst) || mz_check_op(lst))
	{
		putstr_fd("starshell: syntax error\n", 2);
		return (-1);
	}
	else
		return (0);
}
