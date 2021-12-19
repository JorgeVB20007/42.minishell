/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:15:35 by jvacaris          #+#    #+#             */
/*   Updated: 2021/12/19 23:52:32 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
!	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!	| This whole file is outdated. |
!	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

static int	still_command_check(char *list)
{
	char	*assist;

	if (!list)
		return (0);
	assist = adv_qm_rem(list, 0);
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

static char	*get_command_path(char *command, char **envp)
{
	int		idx;
	char	*str_att;
	char	**path_list;

	idx = 0;
	while (envp[idx] && ft_strncmp(envp[idx], "PATH=", 5))
		idx++;
	if (!envp[idx])
	{
		write(2, "Error: env variable 'PATH' not found.\n", 38);
		return (NULL);
	}
	path_list = ft_split(&envp[idx][5], ':');
	idx = 0;
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

void	exec_command(char **list, char **envp)
{
	int		idx;
	char	**red_list;
	char	*assist;
	int		frk;

	idx = 0;
	while (still_command_check(list[idx]))
		idx++;
	red_list = calloc(sizeof(char *), idx + 1);
	idx = -1;
	assist = adv_qm_rem(list[0], 0);
	if (!access(assist, X_OK))
		red_list[++idx] = get_last_file(assist);
	while (still_command_check(list[++idx]))
		red_list[idx] = list[idx];
	red_list[idx] = NULL;
	if (access(assist, X_OK))
	{
		free(assist);
		assist = get_command_path(red_list[0], envp);
	}
	if (!assist)
		return ;
	frk = fork();
	if (!frk)
	{
		if (execve(assist, red_list, envp) < 0)
			perror("Error:");
	}
	wait(NULL);
	free(assist);
}
