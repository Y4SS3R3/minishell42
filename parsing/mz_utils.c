/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:30:52 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/31 21:24:45 by ymassiou         ###   ########.fr       */
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

char	*ft_strdup_mz(const char *s1)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = (char *) malloc(ft_strlen_mz(s1) + 1);
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

char	*ft_substr_mz(char const *s, unsigned int start, size_t len)
{
	size_t	tol;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen_mz(s))
		return (ft_strdup_mz(""));
	if (len > ft_strlen_mz(s) - start)
		tol = ft_strlen_mz(s) - start;
	else
		tol = len;
	sub = malloc(tol + 1);
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

char	*ft_strjoin_mz(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_mz(s2));
	if (!s2)
		return (ft_strdup_mz(s1));
	i = -1;
	j = 0;
	final = malloc(ft_strlen_mz(s1) + ft_strlen_mz(s2) + 1);
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

void	mz_free_char(char *s)
{
	free(s);
	s = NULL;
}

t_token	*ft_lstnew_mz(char *cmd)
{
	t_token	*head;

	head = NULL;
	head = (t_token *)malloc(sizeof(t_token));
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
