
#include "../minishell.h"

t_token	*mz_last_scan(t_list *head, t_shell *data)
{
	t_token	*list;

	list = NULL;
	while (head)
	{
		if (head->nature == -1)
			mz_make_cmd(&list, &head, data);
		else if (head->nature == 32)
			head = head->next;
		else
			mz_make_special(&list, &head, data);
	}
	return (list);
}
