#include "minishell.h"

#define COMMAND_NOT_FOUND "Error: command {0} not found.\n"
#define PATH_NOT_FOUND "Error: env variable 'PATH' not found.\n"

/*
?   (Continuación de la función de abajo)
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
		log_error(PATH_NOT_FOUND, 1);
		return (NULL);
	}
	path_list = ft_split(paths, ':');
	while (path_list[idx])
	{
		str_att = ft_strslashjoin(path_list[idx++], command);
		if (!access(str_att, X_OK))
			break ;
		free(str_att);
		str_att = NULL;
	}
	megafree(&path_list);
	if (str_att == NULL)
		log_error_free(ft_strreplace(COMMAND_NOT_FOUND, "{0}", command), 127);
	return (str_att);
}

/*
?   Esta función te saca el path correcto para el comando que le pasas.
?   Si le pasas la dirección a un ejecutable, te devuelve esa misma
?   dirección malloqueada.
*/
char	*new_getpath(char *raw_cmd, t_str **env_list)
{
	int a;

	a = 0;
	while (raw_cmd[a] && raw_cmd[a] == '.')
		a++;
	if (raw_cmd[a] == '/')							//TODO		This isn't detecting the first '/' properly :(
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
?   Misma función que la de abajo, pero te saca los parámetros
?   quitando las redireccioones en lugar de lo contrario.

*   Ej:
	cat
	-e
	a.txt

?   NOTA: Hay que pasarle un puntero al primer parámetro del que se quieran sacar los parámetros.
	cat -n  <  a.txt  |  grep Error  |  wc -la  >  b.txt  |  cat -e  << end
!   ^~~~~~ (1) ~~~~~	 ^~~ (2) ~~	 ^~~~~~ (3) ~~~~~	 ^~~~~ (4) ~~~~
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
		else
			a++;
	}
	ret = ft_calloc(sizeof(char *), c + 1);
	ret[0] = ft_strdup(&fst[b]);
	free(fst);
	a = -1;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] != '<' && list[a][0] != '>')
			ret[c++] = adv_qm_rem(list[a], 0);
		else
			a++;
	}
	ret[c] = NULL;

	c = 0;
	while (ret[c])
	{
		c++;
	}
	return (ret);
}

/*
?   Este recibe los parámetros spliteados, y devuelve todas las
?	redirecciones en formato:
*   '<' '>' '<<' '>>'
?   y el archivo en el siguiente puntero.

*   Ej:
	>
	a.txt
	<<
	"goodbye"


?   NOTA: Hay que pasarle un puntero al primer parámetro del que se
?	quieran sacar las redirecciones.
	cat -n  <  a.txt  |  grep Error  |  wc -la  >  b.txt  |  cat -e  << end
!   ^~~~~~ (1) ~~~~~	 ^~~ (2) ~~	 ^~~~~~ (3) ~~~~~	 ^~~~~ (4) ~~~~
*/
char	**getredirections(char **list)
{
	int		a;
	int		c;
	char	**ret;

	a = -1;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] == '<' || list[a][0] == '>')
			c += 2;
	}
	ret = ft_calloc(sizeof(char *), c + 1);
	a = -1;
	c = 0;
	while (list[++a] && list[a][0] != '|')
	{
		if (list[a][0] == '<' || list[a][0] == '>')
		{
			ret[c++] = adv_qm_rem(list[a++], 0);
			ret[c++] = adv_qm_rem(list[a], 0);
		}
	}
	ret[c] = NULL;
	return (ret);
}

int  put_params_in_struct(char **list, t_str **env_list, t_red **red_list)
{
	int		a;
	int		items;
	t_red	*item_red;

	a = 0;
	items = 0;
	while (list[a])
	{
		item_red = lst_red_new();
		items++;
		item_red -> params = getparams(&list[a]);
		item_red -> path = new_getpath(item_red -> params[0], env_list);
		item_red -> redirs = getredirections(&list[a]);
		item_red -> pip_in = 0;
		item_red -> pip_out = 1;
		lst_red_add_back(red_list, item_red);
		while (list[a] && list[a][0] != '|')
			a++;
		if (list[a])
			a++;
	}
	return (items);
}
