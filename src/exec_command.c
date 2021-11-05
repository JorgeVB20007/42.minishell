#include "minishell.h"

static int	still_command_check(char *list)
{
	char	*assist;

	if (!list)
		return (0);
	assist = adv_qm_rem(list);
	if (list[0] == '|')
		return (0);
	if (!ft_strncmp(assist, ">\0", 2) || !ft_strncmp(assist, ">>\0", 3))
		return (0);
	if (!ft_strncmp(assist, "<\0", 2) || !ft_strncmp(assist, "<<\0", 3))
		return (0);
	return (1);
}

static char	*get_last_file(char *orig)
{
	char	**assist;
	char	*res;
	int		a;

	a = 0;
	assist = ft_split(orig, '/');
	if (!assist[1])
	{
		res = ft_strdup(assist[0]);
		free(assist[0]);
		free(assist);
		return (res);
	}
	while (assist[a])
		a++;
	res = ft_strdup(assist[a - 1]);
	a = 0;
	while (assist[a])
		free(assist[a++]);
	free(assist);
	return (res);
}

char	*get_command_path(char *command, char **envp)
{
	int		idx;
	char	*str_att;
	char	**path_list;

	idx = 0;
	while(envp[idx] && ft_strncmp(envp[idx], "PATH=", 5))
		idx++;
	if (!envp[idx])
	{
		write(1, "Error: env variable 'PATH' not found.\n", 38);
		return (NULL);
	}
		
	path_list = ft_split(&envp[idx][5], ':');
	idx = 0;
	while (envp[idx])
	{
		str_att = ft_strslashjoin(path_list[idx], command);
		if (!access(str_att, X_OK))
		{
			megafree(&path_list);
			return (str_att);
		}
		free(str_att);
		idx++;
	}
	return (NULL);
}

void	exec_command(char **list, char **envp)
{
	int		idx;
	char	**red_list;
	char	*assist;

	idx = 0;
	while (still_command_check(list[idx]))
		idx++;
	red_list = calloc(sizeof(char *), idx + 1);
	idx = -1;
	assist = adv_qm_rem(list[0]);
	if (!access(assist, X_OK))
	{
		red_list[++idx] = get_last_file(assist);
//		free(red_list[0]);
	}
	while (still_command_check(list[++idx]))
		red_list[idx] = list[idx];
	red_list[idx] = NULL;
	if (access(assist, X_OK))
	{
		free(assist);
		assist = get_command_path(red_list[0], envp);
	}
	execve(assist, list, envp);
	free(assist);
}
/* 
 *	DONE: Check if first argument is an adress or a command.
 	TODO: If it's not an adress, create function to iterate possibilities.
*/

/*
int main(int argc, char **argv, char **envp)
{
	char	**hello;
	int		pip[2];
	int		old;

	old = dup(1);
	pipe(pip);
	dup2(pip[0], STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	write(1, "Hello\n\n\n", 8);
	argc = 0;
	argv = NULL;
	close(pip[1]);
	hello = calloc(sizeof(char *), 3);
	hello[0] = calloc(sizeof(char), 4);
	hello[0][0] = 'c';
	hello[0][1] = 'a';
	hello[0][2] = 't';
	hello[0][3] = 0;
	hello[1] = calloc(sizeof(char), 3);
	hello[1][0] = '-';
	hello[1][1] = 'e';
	hello[1][2] = 0;
	hello[2] = calloc(sizeof(char), 3);
	hello[2][0] = 'M';
	hello[2][1] = 'a';
	hello[2][2] = 'k';
	hello[2][3] = 'e';
	hello[2][4] = 'f';
	hello[2][5] = 'i';
	hello[2][6] = 'l';
	hello[2][7] = 'e';
	hello[2][8] = 0;
	hello[2] = NULL;
	dup2(old, 1);
	execve("/bin/cat", hello, envp);
	close(pip[0]);
	write(1, "Hiiii", 5);
}
*/