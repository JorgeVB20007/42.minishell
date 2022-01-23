/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:26:58 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/23 22:38:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_writing(char **list, int idx, char **assist)
{
	while (list[idx])
	{
		free(*assist);
		*assist = adv_qm_rem(recursive_expand(list[idx++], FALSE), 0);
		ft_putstr_fd(*assist, 1);
		if (list[idx])
			write(1, " ", 1);
	}
}

static int	check_for_flag(char *str)
{
	int	loc;

	loc = 1;
	if (str[0] != '-')
		return (0);
	while (str[loc] == 'n')
		loc++;
	if (ft_isspace(str[loc]) || !str[loc])
		return (1);
	return (0);
}

/*
 * This should recreate the bash funtion "echo".
*/
void	ft_echo(char **list)
{
	int		n_flag;
	char	*assist;
	int		idx;

	n_flag = 0;
	idx = 1;
	if (list[idx] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (1)
	{
		assist = /*adv_qm_rem(*/recursive_expand(ft_strdup(list[idx]),FALSE)/*, 0)*/;
//		dprintf(2, "\n(%s | %s)\n", assist, list[idx]);
		if (!check_for_flag(assist))
			break;
		idx++;
		if (!list[idx])
			break ;
		n_flag = 1;
		free(assist);
	}
/*	if (!strncmp(assist, "-n\0", 3))
	{
		n_flag = 1;
		idx++;
	}*/
	ft_echo_writing(list, idx, &assist);
	if (!n_flag)
		write(1, "\n", 1);
	free(assist);
}

//TODO	echo shouldn't print the final ' ' at the end of a line.
