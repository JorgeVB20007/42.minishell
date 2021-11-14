/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qm_remover.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:43:14 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/13 00:40:53 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
? Function created for the project "minishell"
* The functions below get a string which might contain (or not) quotation
* marks ( ' or " ). The first function (adv_qm_remover) will count the size
* of each item (ignoring q.m.) and then fill them without the quotation
* marks.
! This function doesn't free the first string, as sometimes the previous
! string is needed. A duplicate function could be created if needed.
*/

/*
! This function will probably be removed, as it's been replaced by adv_qm_rem.
*/
char	*qm_remover(char *qm_str)
{
	int		a;
	int		len;
	char	*ret;

	a = 0;
	ret = NULL;
	len = ft_strlen(qm_str);
	if (qm_str[a] != '\'' && qm_str[a] != '"')
		return (ft_strdup(qm_str));
	else
	{
		ret = ft_calloc(sizeof(char), len - 1);
		while (a < len - 2)
		{
			ret[a] = qm_str[a + 1];
			a++;
		}
	}
	return (ret);
}

static int	aqr_count(char *qm_str)
{
	int		a;
	int		count;
	char	qm;

	a = 0;
	count = 0;
	qm = 0;
	while (qm_str[a])
	{
		if (qm_str[a] == '\'' || qm_str[a] == '"')
		{
			if (!qm)
				qm = qm_str[a];
			else if (qm == qm_str[a])
			{
				qm = 0;
				count += 2;
			}
		}
		a++;
	}
	return (count);
}

static void	aqr_filler(char *qm_str, char **result)
{
	int		a;
	int		b;
	char	qm;

	a = 0;
	b = 0;
	qm = 0;
	while (qm_str[a])
	{
		if (qm_str[a] == '\'' || qm_str[a] == '"')
		{
			if (qm == qm_str[a])
				qm = 0;
			else if (qm)
				(*result)[b++] = qm_str[a];
			else if (!qm && ft_strchr(&qm_str[a + 1], qm) == NULL)
				(*result)[b++] = qm_str[a];
			else
				qm = qm_str[a];
		}
		else
			(*result)[b++] = qm_str[a];
		a++;
	}
}

char	*adv_qm_rem(char *qm_str, int b_free)
{
	char	*result;
	int		less_chars;

	less_chars = aqr_count(qm_str);
	result = NULL;
	if (!less_chars)
		return (ft_strdup(qm_str));
	result = ft_calloc((sizeof(char)), ft_strlen(qm_str) - less_chars + 1);
	aqr_filler(qm_str, &result);
	if (b_free)
		free(qm_str);
	return (result);
}
