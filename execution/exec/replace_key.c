
#include "../../minishell.h"

void	initialize_replace_info(t_replace_info *info,
	char *result, size_t rem_len)
{
	info->result = result;
	info->res_i = 0;
	info->i = 0;
	info->rem_len = rem_len;
	info->first_occurrence = 1;
}

void	handle_match(t_replace_info *info)
{
	if (info->first_occurrence)
	{
		info->result[info->res_i] = '$';
		info->res_i++;
		info->first_occurrence = 0;
	}
	info->i += info->rem_len;
}

void	handle_no_match(t_replace_info *info, char *original)
{
	info->result[info->res_i] = original[info->i];
	info->res_i++;
	info->i++;
}

void	process_string(t_replace_info *info, char *original, char *to_remove)
{
	size_t	orig_len;

	orig_len = ft_strlen(original);
	while (info->i < orig_len)
	{
		if (ft_strncmp(&original[info->i], to_remove, info->rem_len) == 0)
			handle_match(info);
		else
			handle_no_match(info, original);
	}
	info->result[info->res_i] = '\0';
}

char	*replace_key(char *original, char *to_remove, t_shell *data)
{
	t_replace_info	info;
	size_t			new_len;

	if (original == NULL || to_remove == NULL)
		return (NULL);
	new_len = ft_strlen(original);
	info.result = which_malloc(LOOP, new_len + 1, data);
	if (info.result == NULL)
		return (NULL);
	initialize_replace_info(&info, info.result, ft_strlen(to_remove));
	process_string(&info, original, to_remove);
	return (info.result);
}
