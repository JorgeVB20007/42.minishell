#include "minishell.h"

void ft_heredoc(int *fdi, char *last_line)
{
	int		pip[2];
	char	*str_got;
	int		ll_len;

	ll_len = ft_strlen(last_line) + 1;
	pipe(pip);
	*fdi = pip[0];
	dup2(pip[0], 0);
	while (1)
	{
//		write(2, "(1) ", 4);
		str_got = readline("> "); // ! readline doesn't stop after enter is clicked for some reason :(
//		write(2, "(2) ", 4);
		if (!ft_strncmp(str_got, last_line, ll_len))
			break ;
//		write(2, "(3) ", 4);
		ft_putstr_fd(str_got, pip[1]);
//		write(2, "(4) ", 4);
		ft_putstr_fd("\n", pip[1]);
//		write(2, "(5) ", 4);
		free(str_got);
	}
	close(pip[1]);
}