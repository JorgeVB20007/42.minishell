#include "minishell.h"

/*
?	(Continuación de la función de abajo)
*/
char	*new_get_command_path(char *command, t_str **env_list)
{
	int		idx;
	char	*str_att;
	char	*paths;
	char	**path_list;

	idx = 0;
	paths = ft_getenv(env_list, "PATH");
	if (!paths[0])
	{
		write(2, "Error: env variable 'PATH' not found.\n", 38);
		return (NULL);
	}
	path_list = ft_split(paths, ':');
	while (path_list[idx])
	{
		str_att = ft_strslashjoin(path_list[idx++], command);
		if (!access(str_att, X_OK))
		{
			megafree(&path_list);
			return (str_att);
		}
		free(str_att);
	}
	ft_putstr_fd("Error: command ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(" not found.\n", 2);
	return (NULL);
}

/*
?	Esta función te saca el path correcto para el comando que le pasas.
?	Si le pasas la dirección a un ejecutable, te devuelve esa misma
?	dirección malloqueada.
*/
char	*new_getpath(char *raw_cmd, t_str **env_list)
{
	int	a;

	a = 0;
	while (raw_cmd[a] && raw_cmd[a] == '.')
		a++;
	if (raw_cmd[a] == '/')
	{
		if (!access(new_get_command_path(raw_cmd, env_list), X_OK))
			return (ft_strdup(raw_cmd));
		else
			perror("Error:");
		return (NULL);
	}
	return (new_get_command_path(raw_cmd, env_list));
}

/*
?	Misma función que la de abajo, pero te saca los parámetros 
?	quitando las redireccioones en lugar de lo contrario.

*	Ej:
	cat
	-e
	a.txt

?	NOTA: Hay que pasarle un puntero al primer parámetro del que se quieran sacar los parámetros.
	cat -n  <  a.txt  |  grep Error  |  wc -l  >  b.txt  |  cat -e  << end
!	^      (1)           ^    (2)       ^       (3)         ^      (4)
*/
char	**getparams(char **list)
{
	int		a;
	int		b;
	int		c;
	char	*fst;
	char	**ret;

	a = -1;
	b = -1;
	c = 0;
	fst = adv_qm_rem(list[0], 0);
	while (fst[++a])
	{
		if (fst[a] == '/')
			b = a;
	}
	a = -1;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] != '<' && list[a][0] != '>')
			c++;
	}
	ret = ft_calloc(sizeof(char *), c + 1);
	ret[0] = ft_strdup(&fst[b]);
	free(fst);
	a = 0;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] != '<' && list[a][0] != '>')
			ret[c++] = adv_qm_rem(list[a], 0);
	}
	ret[c] = NULL;
	return (ret);
}

/*
?	Este recibe los parámetros spliteados, y devuelve todas las redirecciones en formato:
*	'<' '>' '<<' '>>' 
?	y el archivo en el siguiente puntero.

*	Ej:
	>
	a.txt
	<<
	"goodbye"


?	NOTA: Hay que pasarle un puntero al primer parámetro del que se quieran sacar las redirecciones.
	cat -n  <  a.txt  |  grep Error  |  wc -l  >  b.txt  |  cat -e  << end
!	^      (1)           ^    (2)       ^       (3)         ^      (4)
*/
char	**getredirections(char **list)
{
	int		a;
	int		b;
	int		c;
	char	**ret;

	a = -1;
	b = -1;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] == '<' && list[a][0] == '>')
			c += 2;
	}
	ret = ft_calloc(sizeof(char *), c + 1);
	ret[0] = ft_strdup(&fst[b]);
	a = 0;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] == '<' && list[a][0] == '>')
		{
			ret[c++] = adv_qm_rem(list[a], 0);
			ret[c++] = adv_qm_rem(list[a], 0);
		}
	}
	ret[c] = NULL;
	return (ret);
}

/*
?	Aquí se supone que metía las cosas en la estructura.
!	Epic fail. 
*/
t_red	**put_params_in_struct(char **list, t_str **env_list)
{
	int		a;
	int		b;
	t_red	*new_block;
	t_red	*prev_block;
	t_red	**ret;

	a = 0;
	b = 0;
	prev_block = NULL;
	ret = NULL;
	write(1, "1", 1);
	while (list[a])
	{
		write(1, ".", 1);
		new_block = malloc(sizeof(t_red));
		write(1, "a", 1);
		if (!ret)
			ret = &new_block;
		write(1, "b", 1);
		if (prev_block)
			prev_block -> next = new_block;
		write(1, "c", 1);
		new_block -> path = new_getpath(adv_qm_rem(list[a], 0), env_list);
		write(1, "d", 1);
		new_block -> params = getparams(&list[a]);
		write(1, ",", 1);
		prev_block = new_block;
		b = a;
		while (list[a] && list[a][0] != '|')
			a++;
		write(1, "-", 1);
		if (list[a])
			a++;
	}
	write(1, "3", 1);
	new_block -> next = NULL;
	write(1, "4", 1);
	prev_block = *ret;
	printf(" ** %p **", (*prev_block).next);
	while ((*prev_block).next != NULL)
	{
		write(1, " ! ", 3);
		printf("\n > %s <\n", prev_block -> path);
		prev_block = prev_block -> next;
	}
	return (ret);
}



/*
?	Aquí quería llamar a una función para rellenar la lista enlazada
?	para luego crear forks en un while y pasarle a cada fork su item de la
?	lista con su path, sus parámetros y todas sus redirecciones.

*	Lo que es seguro es que cada item de la lista es un comando, y se 
*	separan los unos de los otros al encontrarse con un | sin comillas.
*/
void	new_redirections(char **list, t_str **env_list)
{
	t_red	**sep_params;
	t_red	*temp;

	sep_params = put_params_in_struct(list, env_list);
	temp = (*sep_params)->next;


}
