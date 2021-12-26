/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:17:51 by emadriga          #+#    #+#             */
/*   Updated: 2021/12/26 18:17:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_uppperhundreds(int num_len, int pos)
{
	char	*ntochar;
	int		digits;

	digits = num_len - pos;
	if (digits % 3 == 1 && digits > 3)
	{
		ntochar = ft_calloc(sizeof(char), digits);
		ft_memset(ntochar, '0', digits);
		ntochar[0] = '1';
		write(1, " ", 1);
		ft_search_word(ntochar);
		write(1, " ", 1);
		free(ntochar);
	}
}

static void	ft_units( int *pos, char *number)
{
	char	ntochar[4];

	if (number[*pos] != '0')
	{
		ntochar[0] = number[*pos] + '\0';
		ntochar[1] = '\0';
		ft_search_word(ntochar);
	}
}

static void	ft_tens(int *pos, char *number)
{
	char	ntochar[4];

	if (number[*pos] != '0')
	{
		ntochar[0] = number[*pos] + '\0';
		if (number[*pos] == '1')
		{
			ntochar[1] = number[*pos + 1] + '\0';
			(*pos)++;
		}
		else
			ntochar[1] = '0';
		ntochar[2] = '\0';
		ft_search_word(ntochar);
	}
}

static int	ft_downhundreds(int *pos, int prev_pos, char *number, int num_len)
{
	int	digits;

	digits = num_len - *pos;
	if (digits % 3 == 1)
	{
		if (prev_pos == *pos - 1)
			ft_putstr_fd("-", STDOUT_FILENO);
		ft_units(pos, number);
	}
	else if (digits % 3 == 2)
	{
		if (prev_pos == *pos - 1)
			ft_putstr_fd(" and ", STDOUT_FILENO);
		ft_tens(pos, number);
	}
	else if (digits % 3 == 0)
	{
		ft_units(pos, number);
		write(1, " ", 1);
		ft_search_word("100");
	}
	return (*pos);
}

void	translate_number(char *number)
{
	int	index;
	int	numlen;
	int	prev_index;

	index = -1;
	prev_index = 0;
	if (number[index + 2] == '\0')
		ft_search_word(&number[index]);
	numlen = ft_strlen(number);
	while (number[++index])
	{
		prev_index = ft_downhundreds(&index, prev_index, number, numlen);
		ft_uppperhundreds(numlen, index);
	}
	free(number);
}
