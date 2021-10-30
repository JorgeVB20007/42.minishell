#include "minishell.h"

/*
 * This should recreate the bash funtion "echo".
*/
void	ft_echo(char **list, int *idx)
{
	int		n_flag;
	char	*assist;

	n_flag = 0;
	(*idx)++;
	if (list[*idx] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	assist = adv_qm_rem(list[*idx]);
	if (!strncmp(assist, "-n\0", 3))
	{
		n_flag = 1;
		(*idx)++;
	}
	while (list[*idx])
	{
		free(assist);
		assist = adv_qm_rem(list[(*idx)++]);
		ft_putstr_fd(assist, 1);
		write(1, " ", 1);
	}
	if (!n_flag)
		write(1, "\n", 1);
	free(assist);
}
