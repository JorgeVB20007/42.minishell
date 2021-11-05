#include "minishell.h"

/**
 * * This should recreate the bash funtion "export".
 * * Add record to enviroment variables list
 * @param env_list	enviroment list
*/
void	ft_export(t_str *env_list, char * record)
{
	char	*env_desc;

	env_desc = NULL;
	env_desc = ft_substr(*record, 0, ft_strchr(*record, '=') - *record + 1);
	//TODO Log with errors and locations (function throwing them) 'd be great
	ft_lst_str_delete(env_list, env_desc);
	ft_lstadd_front(env_list, record); //record should came with malloc
}
