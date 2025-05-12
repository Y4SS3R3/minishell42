
#include "../../minishell.h"

void	append_to_var(char **name, t_shell *data)
{
	int		len;
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	str = *name;
	if (str == NULL)
		return ;
	if (data->exapp == 1)
	{
		len = ft_strlen(str);
		tmp = which_malloc(GLOBAL, len, data);
		if (tmp == NULL)
			return ;
		while (str[i] != '+' && str[i])
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = 0;
		*name = tmp;
	}
}

int	add_hide(t_shell *data, char *res, char *name)
{
	t_list	*new;

	if (data->add_equal == 0)
	{
		data->add_equal = 1;
		new = ym_lstnew(res, GLOBAL, data);
		new->hide = 1;
		if (!search_fetch_list(data->envl, name, data))
			ym_lstadd_back(&data->envl, new);
		return (-1);
	}
	return (0);
}

void	add_equal(int flag, char **res, t_shell *data, char *name)
{
	char	*tmp;

	if (flag)
		*res = ft_strjoin(*res, "=", GLOBAL, data);
	if (data->exapp == 1)
	{
		tmp = search_fetch_add(data->envp, name, data);
		if (tmp)
			*res = tmp;
		data->exapp = 0;
	}
}

void	append_to_env_util(t_shell *data, int flag, t_list	*new, char *name)
{
	if (!flag)
		new->hide = 1;
	search_remove(&data->envl, name, data);
	ym_lstadd_back(&data->envl, new);
}

void	append_to_env(char *name, char *value, int flag, t_shell *data)
{
	char	*res;
	t_list	*new;

	res = NULL;
	append_to_var(&name, data);
	if (name == NULL)
		return ;
	res = ft_strjoin(res, name, GLOBAL, data);
	if (add_hide(data, res, name))
		return ;
	add_equal(flag, &res, data, name);
	if (value && ft_strchr(value, '*'))
	{
		value = get_entry_content(value, data);
		if (value == NULL)
			return ;
		value = trim_string(value, data);
	}
	res = ft_strjoin(res, value, GLOBAL, data);
	if (res == NULL)
		return ;
	new = ym_lstnew(res, GLOBAL, data);
	if (new == NULL)
		return ;
	append_to_env_util(data, flag, new, name);
}
