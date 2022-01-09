/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:17:51 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/09 12:04:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_uppperhundreds(int num_len, int pos, char *number, \
								char **sleep_argv)
{
	char	*ntochar;
	int		digits;

	digits = num_len - pos;
	if (digits % 3 == 1 && digits > 3)
	{
		if (pos > 2 && !ft_strncmp(&number[pos - 2], "000", 3))
			;
		else
		{
			ntochar = ft_calloc(sizeof(char), digits);
			ft_memset(ntochar, '0', digits);
			ntochar[0] = '1';
			write(1, " ", 1);
			ft_search_word(ntochar, sleep_argv);
			write(1, " ", 1);
			free(ntochar);
		}
	}
}

static void	ft_units( int *pos, char *number, char **sleep_argv)
{
	char	ntochar[4];

	ntochar[0] = number[*pos] + '\0';
	ntochar[1] = '\0';
	ft_search_word(ntochar, sleep_argv);
}

static void	ft_tens(int *pos, char *number, char **sleep_argv)
{
	char	ntochar[4];

	ntochar[0] = number[*pos] + '\0';
	ntochar[2] = '\0';
	if (number[*pos] == '1')
	{
		ntochar[1] = number[*pos + 1] + '\0';
		(*pos)++;
		ft_search_word(ntochar, sleep_argv);
	}
	else
	{
		ntochar[1] = '0';
		ft_search_word(ntochar, sleep_argv);
		if (number[*pos + 1] != '0')
			ft_putstr_fd("-", STDOUT_FILENO);
	}
}

static void	ft_downhundreds(int *pos, char *number, int num_len, \
							char **sleep_argv)
{
	int	digits;

	digits = num_len - *pos;
	if (digits % 3 == 1)
		ft_units(pos, number, sleep_argv);
	else if (digits % 3 == 2)
		ft_tens(pos, number, sleep_argv);
	else if (digits % 3 == 0)
	{
		ft_units(pos, number, sleep_argv);
		write(1, " ", 1);
		ft_search_word("100", sleep_argv);
		if (ft_strncmp(&number[*pos + 1], "00", 2))
			ft_putstr_fd(" and ", STDOUT_FILENO);
	}
}

void	translate_number(int nbr, char **sleep_argv)
{
	int		index;
	int		numlen;
	char	*number;

	index = -1;
	number = ft_itoa(nbr);
	if (number[index + 2] == '\0')
		ft_search_word(&number[index], sleep_argv);
	numlen = ft_strlen(number);
	while (number[++index])
	{
		if (number[index] != '0')
			ft_downhundreds(&index, number, numlen, sleep_argv);
		ft_uppperhundreds(numlen, index, number, sleep_argv);
	}
	free(number);
}
