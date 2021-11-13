/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modstrcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 23:52:24 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/11 00:00:40 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modstrcmp(char *str1, char *str2)
{
	int	a;

	a = 0;
	if (str1 == NULL && str2 == NULL)
		return (0);
	else if (str1 == NULL)
		return ((int)str2[a]);
	else if (str2 == NULL)
		return (0 - (int)str1[a]);
	while (str1[a] && str2[a])
	{
		if (str1[a] != str2[a])
			return ((int)str2[a] - (int)str1[a]);
		a++;
	}
	if (!str1[a] && !str2[a])
		return (0);
	return ((int)str2[a] - (int)str1[a]);
}
