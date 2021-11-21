#include "minishell.h"

void	new_exec_command(t_red *red_node, char **env)
{
	int		a;
	int		fdi;
	int		fdo;
	char	*no_qm;

	a = 0;
	fdi = 0;
	fdo = 0;
	dup2(red_node -> pip_in, 0);
	dup2(red_node -> pip_out, 1);
	while (red_node -> redirs[a])
	{
		no_qm = adv_qm_rem(red_node -> redirs[a + 1], 0);
		if (!ft_strcmp(red_node -> redirs[a], "<"))
		{
			if (fdi)
				close(fdi);
			fdi = open(no_qm, O_RDONLY, 0666);
			dup2(fdi, 0);
		}
		if (!ft_strcmp(red_node -> redirs[a], ">"))
		{
			if (fdo)
				close(fdo);
			fdo = open(no_qm, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(fdo, 1);
		}
		if (!ft_strcmp(red_node -> redirs[a], ">>"))
		{
			if (fdo)
				close(fdo);
			fdo = open(no_qm, O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(fdo, 1);
		}
		if (!ft_strcmp(red_node -> redirs[a], "<<"))
		{
			if (fdi)
				close(fdi);
			if (ft_strchr(red_node -> redirs[a + 1], '\'') || ft_strchr(red_node -> redirs[a + 1], '"'))
				ft_heredoc_qm(&fdi, no_qm);
			else
				ft_heredoc(&fdi, red_node -> redirs[a + 1]);
			dup2(fdi, 0);
		}
		free(no_qm);
		a += 2;
	}
	execve(red_node -> path, red_node -> params, env);
}