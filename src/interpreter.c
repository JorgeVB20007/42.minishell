#include "minishell.h"

/*
* This function is in charge of getting the list of parameters, 
* identify the command given and execute it.
*/
void	interpreter(char **list)
{
	int		idx;
	char	*assist;

	idx = 0;
	while (list[idx])
	{
		assist = qm_remover(list[idx]);
		if (!ft_strncmp(assist, "echo\0", 5))
			ft_echo(list, &idx);
		free(assist);
		if (list[idx])
			idx++;
	}
}
