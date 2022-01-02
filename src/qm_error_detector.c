/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qm_error_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:22:19 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/02 17:00:07 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* * This function detects if there's quotation marks unclosed through the input
* * given. Quotation marks inside other types of quotation marks are excluded.
* * If all goes well, the value 0 is returned.
* @return 		ERNNO code is returnerd
*/
int	qm_error_detector(char *str)
{
	int		a;
	char	qm;

	a = 0;
	qm = 0;
	while (str[a])
	{
		if ((str[a] == '\'' || str[a] == '"') && (!a || str[a - 1] != '\\'))
		{
			if (!qm)
				qm = str[a];
			else if (qm == str[a])
				qm = 0;
		}
		a++;
	}
	if (qm)
	{
		ft_putstr_fd("minishell: unclosed quotation marks\n", 2);
		return (1);
	}
	return (0);
}


