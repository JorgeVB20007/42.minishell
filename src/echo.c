#include "minishell.h"

void	ft_echo(char **list, int *idx)
{
	int		n_flag;
	char	*assist;

	n_flag = 0;
	(*idx)++;
	assist = qm_remover(list[*idx]);
	if (list[*idx] == NULL)
		write(1, "\n", 1);
	else
	{
		if (!strncmp(assist, "-n\0", 3))
		{
			n_flag = 1;
			(*idx)++;
		}
		while (list[*idx])
		{
			ft_putstr_fd(list[*idx], 1);
			write(1, " ", 1);
			(*idx)++;
		}
		if (!n_flag)
			write(1, "\n", 1);
	}
	free(assist);
}