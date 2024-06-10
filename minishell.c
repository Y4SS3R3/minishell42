/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:00:38 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 12:43:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print2DUtil(t_token* root, int space)
{
    if (root == NULL)
        return;
    space += 10;
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->cmd);
    print2DUtil(root->left, space);
}

void print2D(t_token* root)
{
    print2DUtil(root, 0);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_list	*envp;
	t_token	*linked;
	t_token	*l;
	t_shell data;

	(void)av;
	if (ac != 1)
	{
		printf("Error!\nPlease execute the program without arguments!\n");
		return (1);
	}
	check_env(&data, env);
	check_potential_path(&data);
	envp = env_parse(env);
	while (1)
	{
		s = readline("minishell:");
		if (!s)
		{
			printf("Error!\nreadline returned NULL\n");
			return (1);
		}
		linked = mz_parser(s);
		l = linked;
		data.the_tree = ft_tree(&linked, &data);
		// print2D(data.the_tree);
		dfs_tree(data.the_tree, &data);
		free(s);

		int i = 0;
		// linked = l;
		// while (linked)
		// {
		// 	i = 0;
		// 	printf("\n\n%s  --> %i\n", linked->cmd, linked->nature);
		// 	while (linked->args && linked->args[i])
		// 	{
		// 		printf("arg_%i ->> [%s]\n", i, linked->args[i]);
		// 		i++;
		// 	}
		// 	linked = linked->next;
		// }
	}
	return (0);
}





// ls -la | ( cat -e && wc -l && echo '$VAR') | grep "something i want" > outfile || < infile cat

/*  !! TO FREE ENVP !!!!

	t_list	*test2;
	test2 = envp;
	while (envp)
	{
		printf("%s\n", envp->s);
		envp = envp->next;
	}
	envp = NULL;
	while (test2)
	{
		envp = test2;
		free(test2->s);
		test2 = test2->next;
		free(envp);
	}
*/
