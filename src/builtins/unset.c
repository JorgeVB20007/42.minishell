#include "minishell.h"

/**
 * * This should recreate the bash funtion "unset".
 * * Clear enviroment variables list
 * @param env_list	enviroment list
*/
void	ft_unset(t_str *env_list)
{
	ft_lst_str_free(env_list);
}
