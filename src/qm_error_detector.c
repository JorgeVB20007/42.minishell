/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qm_error_detector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:22:19 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/21 17:27:34 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_OPEN_REDIR "minishel: syntax error near \
unexpected token `%s'\n"
#define LIT_NEWLINE "newline"

enum e_token
{
	NONE,
	PIPE,
	REDIRECTION
};

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
		write(1, "minishell: unclosed quotation marks\n", 37);
		return (1);
	}
	return (0);
}

/**
 * * Eval token to check between EOF, PIPE, REDIRECTION or NONE
 * @param token	token
 * @return 		token identiifcator 
*/
static int	eval_token(char *token)
{
	if (!token)
		return (EOF);
	else if (!ft_strcmp(token, "|"))
		return (PIPE);
	else if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<") \
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (REDIRECTION);
	return (NONE);
}

/**
 * * Detects open pipes & redirections
 * @param array	array of args (input splited in useful tokens)
 * @return 		ERNNO code is returnerd
*/
int	has_pipe_redir_open(char **array)
{
	int		current;
	int		next;
	char	*error_near_token;

	error_near_token = NULL;
	if (eval_token(*array) == PIPE)
		error_near_token = ft_strdup(*array);
	while (*array != NULL && !error_near_token)
	{
		current = eval_token(*array++);
		next = eval_token(*array);
		if ((current == REDIRECTION || current == PIPE) && next == EOF)
			error_near_token = ft_strdup(LIT_NEWLINE);
		else if (current == REDIRECTION && next != NONE)
			error_near_token = ft_strdup(*array);
		else if (current == PIPE && next == PIPE)
			error_near_token = ft_strdup(*array);
	}
	if (error_near_token != NULL)
	{
		printf(ERROR_OPEN_REDIR, error_near_token);
		free(error_near_token);
		return (258);
	}
	return (0);
}
