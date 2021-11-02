#include "minishell.h"

/*
* This has no use yet. It might be used later to count how many
* pipes are required and create an appropriate amount of forks.
*/
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
	return (count);
}

/*
* This funtion looks for redirection signs before a '|'
* or the last parameter is found. When it finds one, it'll
* open the file indicated right after, and set the STD(IN/OUT)
* to the appropriate file.
TODO	Unsure if SEGFAULT happens if a redir. sign is
TODO	located at the end of the list
*/
void	redirection_finder(char **list, int *fdi, int *fdo, int idx)
{
	while (list[idx] && list[idx][0] != '|')
	{
		if (!ft_strncmp(list[idx], ">\0", 2))
		{
			*fdi = open(list[idx + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(*fdi, 1);
		}
		else if (!ft_strncmp(list[idx], ">>\0", 3))
		{
			*fdi = open(list[idx + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(*fdi, 1);
		}
		else if (!ft_strncmp(list[idx], "<\0", 2))
		{
			*fdo = open(list[idx + 1], O_RDONLY, 0666);
			dup2(*fdo, 0);
		}
		idx++;
	}
}

/*
* This function gets the list of parameters, will look  if the first one
* is a known command and will redirect to the correct funtion.
*/
void	command_finder(char **list, int *idx, t_str **env_list)
{
	char	*assist;

	assist = NULL;
	while (list[*idx] && list[*idx][0] != '|')
	{
		assist = adv_qm_rem(list[*idx]);
		if (!ft_strncmp(assist, "echo\0", 5))
			ft_echo(list, idx);
		if (!ft_strncmp(assist, "pwd\0", 4))
			ft_pwd();
		if (!ft_strncmp(assist, "env\0", 4))
			ft_env(*env_list);
		free(assist);
		if (list[*idx])
			(*idx)++;
	}
}

/*
* This function is in charge of getting the list of parameters
* and call the functions that will redirect the input/output and
* execute the commands given.
? old_stdin and old_stdout are used to store the adress of the
? original STDIN and STDOUT without the need of fork().
*/
void	interpreter(char **list, t_str **env_list)
{
	int		idx;
	int		fdi;
	int		fdo;
	int		old_stdout;
	int		old_stdin;

	idx = 0;
	fdi = 0;
	fdo = 0;
	old_stdout = dup(1);
	old_stdin = dup(0);
	while (list[idx])
	{
		redirection_finder(list, &fdi, &fdo, idx);
		command_finder(list, &idx, env_list);
		if (list[idx])
			idx++;
	}
	if (fdi)
	{
		dup2(old_stdout, 1);
		close(fdi);
	}
	if (fdo)
	{
		dup2(old_stdin, 0);
		close(fdo);
	}
}
