
#include "../../minishell.h"

char	*ex_key_2_assign(char *s, char *key_s, t_shell *data)
{
	char	*res;
	t_info	info;

	info.final = which_malloc(LOOP, ex_mz_size_count(s, key_s), data);
	ex_mz_key_insert(&info, s, key_s);
	res = info.final;
	return (res);
}
