/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:16:07 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/07 00:16:14 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	make_a_pipe(int *fdo, int *nxt)
{
	int	pip_tmp[2];

	pipe(pip_tmp);
	*nxt = pip_tmp[0];
	*fdo = pip_tmp[1];
	dup2(*fdo, 1);
}

/*
* This funtion looks for redirection signs before a '|'
* or the last parameter is found. When it finds one, it'll
* open the file indicated right after, and set the STD(IN/OUT)
* to the appropriate file.
TODO	Unsure if SEGFAULT happens if a redir. sign is
TODO	located at the end of the list
*/
void	redirection_finder(char **list, int *fdi, int *fdo, int *nxt)
{
	int	idx;

	idx = -1;
	*nxt = 0;
	while (list[++idx])
		*nxt += (list[idx][0] == '|');
	if (*nxt)
		make_a_pipe(fdo, nxt);
	idx = 0;
	while (list[idx] && list[idx][0] != '|')
	{
		if (!ft_strncmp(list[idx], ">\0", 2))
		{
			if (*fdi)
				close(*fdi);
			*fdi = open(list[idx + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(*fdi, 1);
		}
		else if (!ft_strncmp(list[idx], ">>\0", 3))
		{
			if (*fdi)
				close(*fdi);
			*fdi = open(list[idx + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(*fdi, 1);
		}
		else if (!ft_strncmp(list[idx], "<\0", 2))
		{
			if (*fdo)
				close(*fdo);
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
static void	command_finder(char **list, int *idx, t_str **env_list)
{
	char	*assist;

	assist = NULL;
	while (list[*idx][0] == '<' || list[*idx][0] == '>')
		*idx += 2;
	assist = adv_qm_rem(list[*idx]);
	if (!ft_strncmp(assist, "echo\0", 5))
		ft_echo(&list[*idx]);
	else if (!ft_strncmp(assist, "pwd\0", 4))
		ft_pwd();
	else if (!ft_strncmp(assist, "env\0", 4))
		ft_env(*env_list);
	else
		exec_command(&list[*idx], env_list_to_vector(env_list));
	free(assist);
	while (list[*idx] && list[*idx][0] != '|')
		(*idx)++;
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
	int	idx;
	int	fdi;
	int	fdo;
	int	old_stds[2];
	int	nxt;

	idx = 0;
	old_stds[1] = dup(1);
	old_stds[0] = dup(0);
	nxt = 0;
	while (list[idx])
	{
		fdi = 0;
		fdo = 0;
		if (nxt)
		{
			fdi = nxt;
			dup2(fdi, 0);
		}
		redirection_finder(&list[idx], &fdi, &fdo, &nxt);
		command_finder(list, &idx, env_list);
		if (list[idx])
			idx++;
		if (fdi)
			close(fdi);
		if (fdo)
			close(fdo);
		dup2(old_stds[1], 1);
		dup2(old_stds[0], 0);
	}
}
