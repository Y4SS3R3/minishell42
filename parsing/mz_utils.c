/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:30:52 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/08 16:37:57 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_mz(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_mz(const char *s1, t_shell *data)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = which_malloc(LOOP, ft_strlen_mz(s1) + 1, data);
	if (cpy == NULL)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr_mz(char const *s, unsigned int start, size_t len, t_shell *data)
{
	size_t	tol;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen_mz(s))
		return (ft_strdup_mz("", data));
	if (len > ft_strlen_mz(s) - start)
		tol = ft_strlen_mz(s) - start;
	else
		tol = len;
	sub = which_malloc(LOOP, tol + 1, data);
	if (!sub)
		return (NULL);
	while (i < tol)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin_mz(char const *s1, char const *s2, t_shell *data)
{
	unsigned int	i;
	unsigned int	j;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_mz(s2, data));
	if (!s2)
		return (ft_strdup_mz(s1, data));
	i = -1;
	j = 0;
	final = which_malloc(LOOP, ft_strlen_mz(s1) + ft_strlen_mz(s2) + 1, data);
	if (!final)
		return (NULL);
	while (s1[++i])
		final[i] = s1[i];
	while (s2[j])
		final[i++] = s2[j++];
	final[i] = '\0';
	return (final);
}

int	mz_search(char *s, int i, char c)
{
	i += 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}

// void	mz_free_char(char *s)
// {
// 	free(s);
// 	s = NULL;
// }

t_token	*ft_lstnew_mz(char *cmd, t_shell *data)
{
	t_token	*head;

	head = NULL;
	head = which_malloc(LOOP, sizeof(t_token), data);
	if (head == NULL)
		return (NULL);
	head->args = NULL;
	head->next = NULL;
	head->previous = NULL;
	head->cmd = cmd;
	head->right = NULL;
	head->left = NULL;
	head->key_d_q = NULL;
	head->key_q = NULL;
	head->nature = 0;
	head->quote = 0;
	head->d_quote = 0;
	head->par = 0;
	head->join = 1;
	return (head);
}
