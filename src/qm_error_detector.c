/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qm_error_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:22:19 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/20 22:26:18 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_OPEN_REDIR "minishel: syntax error near \
unexpected token `%s'\n"
#define LIT_NEWLINE "newline"

/*
* This function detects if there's quotation marks unclosed through the input 
* given. Quotation marks inside other types of quotation marks are excluded.
* If all goes well, the value 0 is returned.
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
		write(1, "minishell: unclosed quotation marks\n", 37);
		return (1);
	}
	return (0);
}

/**
 * * Detects open redirection at the end of str return error if finds one 
 * @param path	path
*/
int	has_last_redirection_open(const char *str)
{
	size_t	len;
	int		ok;
	char	*trim;

	ok = 1;
	trim = ft_strtrim(str, " ");
	len = ft_strlen(trim);
	if (ft_strchr("<>", trim[len - 1]) || !ft_strcmp(&trim[len - 2], ">|"))
		ok = 0;
	if (!ok)
		printf(ERROR_OPEN_REDIR, LIT_NEWLINE);
	free(trim);
	return (ok);
}

/**
 * * Detects open redirections 
 * @param path	path
*/
int	has_redirection_open(const char **array)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	while (array[i])
	{
		if (ft_strcmp(array[i], ">") || ft_strcmp(array[i], "<") \
		|| ft_strcmp(array[i], ">>") || ft_strcmp(array[i++], "<<"))
		{
			if (array[i])
				token = ft_strdup(LIT_NEWLINE);
			else if (ft_strcmp(array[i], ">") || ft_strcmp(array[i], "<") \
				|| ft_strcmp(array[i], ">>") || ft_strcmp(array[i], "<<") \
				|| ft_strcmp(array[i], "|"))
				token = ft_strdup(array[i]);
		}
	}
	if (token != NULL)
	{
		printf(ERROR_OPEN_REDIR, token);
		free(token);
		return (1);
	}	
	return (0);
}
