
#include "../../minishell.h"

int	ft_star(t_token *node, t_shell *data)
{
	star_checkargs(node, data);
	star_checkcmd(node, data);
	return (star_checkredirs(node, data));
}
