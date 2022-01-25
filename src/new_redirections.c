#include "minishell.h"

static void	redir_in(int *fdi, int a, t_red *red_node, int orig_fds[2])
{
	char	*no_qm;

	no_qm = adv_qm_rem(red_node -> redirs[a + 1], 0);
	if (!ft_strcmp(red_node -> redirs[a], "<"))
	{
		if (!access(no_qm, R_OK) && ft_is_directory(no_qm))
		{
			if (*fdi)
				close(*fdi);
			*fdi = open(no_qm, O_RDONLY, 0666);
			dup2(*fdi, 0);
		}
		else
			perror("Error:");
	}
	if (!ft_strcmp(red_node -> redirs[a], "<<"))
	{
		if (*fdi)
			close(*fdi);
		dup2(orig_fds[0], 0);
		if (ft_strchr(red_node -> redirs[a + 1], '\'') || \
		ft_strchr(red_node -> redirs[a + 1], '"'))
			ft_heredoc_qm(fdi, red_node -> redirs[a + 1], orig_fds);
		else
			ft_heredoc(fdi, red_node -> redirs[a + 1], orig_fds);
		dup2(*fdi, 0);
	}
	free(no_qm);
}

static void	redir_out(int *fdo, int a, t_red *red_node, char *no_qm)
{
	if (!ft_strcmp(red_node -> redirs[a], ">"))
	{
		if ((!access(no_qm, W_OK) && ft_is_directory(no_qm)) \
		|| access(no_qm, F_OK))
		{
			if (*fdo)
				close(*fdo);
			*fdo = open(no_qm, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(*fdo, 1);
		}
		else
			perror("Error:");
	}
	if (!ft_strcmp(red_node -> redirs[a], ">>"))
	{
		if (!access(no_qm, R_OK) && ft_is_directory(no_qm))
		{
			if (*fdo)
				close(*fdo);
			*fdo = open(no_qm, O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(*fdo, 1);
		}
		else
			perror("Error:");
	}
}

void	fd_assigner(t_red *red_node, int orig_fds[2])
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
		redir_out(&fdo, a, red_node, no_qm);
		redir_in(&fdi, a, red_node, orig_fds);
		free(no_qm);
		a += 2;
	}
}

static void	apply2pipes(int pip[2], t_red *red_list, int items, char **env_array)
{
	int	ctr;
	int	orig_fds[2];

	ctr = 0;
	orig_fds[0] = dup(0);
	orig_fds[1] = dup(1);
	while (ctr++ != items)
	{
		if (ctr != items)
		{
			pipe(pip);
			red_list -> pip_out = pip[1];
		}
		if (red_list -> pip_in)
			dup2(red_list -> pip_in, 0);
		fd_assigner(red_list, orig_fds);
		if (items == 1)
			command_sorter_no_pipes(red_list, env_array, red_list -> pip_in, red_list -> pip_out);
		else
			command_sorter_wth_pipes(red_list, env_array, pip[0]);
		if (red_list -> pip_in != orig_fds[0])
			close(red_list -> pip_in);
		if (red_list -> pip_out != orig_fds[1])
			close(red_list -> pip_out);
		red_list = red_list -> next;
		if (ctr != items)
			red_list -> pip_in = pip[0];
		dup2(orig_fds[0], 0);
		dup2(orig_fds[1], 1);
	}
}

/*
?   Aquí quería llamar a una función para rellenar la lista enlazada
?   para luego crear forks en un while y pasarle a cada fork su item de la
?   lista con su path, sus parámetros y todas sus redirecciones.
*   Lo que es seguro es que cada item de la lista es un comando, y se
*   separan los unos de los otros al encontrarse con un | sin comillas.
*/
void	new_redirections(char **list, t_str **env_list)
{
	char	**env_array;
	int		items;
	int		pip[2];
	t_red	*red_list;
	int		status;

	red_list = NULL;
	items = put_params_in_struct(list, &red_list);
	env_array = lst_str_to_array(env_list);
	apply2pipes(pip, red_list, items, env_array);
	while (items--)
	{
		wait(&status);
		g_var.current_status = WEXITSTATUS(status);
	}
}
