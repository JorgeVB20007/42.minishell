/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:26:58 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/29 17:10:00 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_writing(char **list, int idx)
{
	while (list[idx])
	{
		ft_putstr_fd(list[idx++], 1);
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
		if (!check_for_flag(list[idx]))
			break ;
		idx++;
		n_flag = 1;
		if (!list[idx])
			break ;
	}
	ft_echo_writing(list, idx);
	if (!n_flag)
		write(1, "\n", 1);
}
