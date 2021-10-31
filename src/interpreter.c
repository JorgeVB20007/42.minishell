#include "minishell.h"

int	am_of_pipes(char **list)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (list[a])
	{
		if (!ft_strncmp(list[a], "|\0", 2))
			count++;
		a++;
	}
	return(count);
}

/*
* This function is in charge of getting the list of parameters, 
* identify the command given and execute it.
*/
void	interpreter(char **list)
{
	int		idx;
	int		idx2;
	char	*assist;

	idx = 0;
	idx2 = 0;
	while (list[idx])
	{
		if (idx == 0 || list[idx] == '|')
		{
			idx2 = idx;
			while (list[idx2] && list[idx2] != '|')
			{
				if (list[idx] == '<')
				idx2++;
			}
		}
		assist = adv_qm_rem(list[idx]);
		if (!ft_strncmp(assist, "echo\0", 5))
			ft_echo(list, &idx);
		if (!ft_strncmp(assist, "pwd\0", 4))
            ft_pwd();
		free(assist);
		if (list[idx])
			idx++;
	}
}
