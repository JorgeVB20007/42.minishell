/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:26:58 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/07 00:28:04 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_writing(char **list, int idx, char **assist)
{
	while (list[idx] && list[idx][0] != '|')
	{
		if (list[idx][0] == '>' || list[idx][0] == '<')
			idx += 2;
		else
		{
			free(*assist);
			*assist = adv_qm_rem(list[idx++]);
			ft_putstr_fd(*assist, 1);
			if (list[idx] && list[idx][0] != '|')
			{
				write(1, " ", 1);
			}
		}
	}
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
	assist = adv_qm_rem(list[idx]);
	if (!strncmp(assist, "-n\0", 3))
	{
		n_flag = 1;
		idx++;
	}
	ft_echo_writing(list, idx, &assist);
	if (!n_flag)
		write(1, "\n", 1);
	free(assist);
}

//TODO	echo shouldn't print the final ' ' at the end of a line.
