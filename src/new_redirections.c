#include "minishell.h"

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
	int		ctr;
	int		frk;
	int		pip[2];
	t_red	*red_list;
	int		status;
	int		orig_fds[2];

	red_list = NULL;
	orig_fds[0] = dup(0);
	orig_fds[1] = dup(1);
	items = put_params_in_struct(list, env_list, &red_list);
	env_array = lst_str_to_array(env_list);
//  assign_pipes(&red_list, items);
	ctr = 0;
	if (items == 1)
	{
		new_exec_command(red_list, env_array, 0);
		dup2(orig_fds[0], 0);
		dup2(orig_fds[1], 1);
	}
	else
	{
		while (ctr++ < items)
		{
			if (ctr != items)
			{
				pipe(pip);
				red_list -> pip_out = pip[1];
			}
			printf(">%d<\n", g_var.status_error);
			frk = fork();
			if (!frk)
				new_exec_command(red_list, env_array, 1);
			if (ctr != items)
				close(pip[1]);
			red_list = red_list -> next;
			if (ctr != items)
				red_list -> pip_in = pip[0];
		}
		ctr = 0;
		while (ctr++ != items)
		{
			wait(&status);
			g_var.status_error = WEXITSTATUS(status);
		}
	}
}