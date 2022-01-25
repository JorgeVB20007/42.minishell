/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:56:38 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/26 00:46:32 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define OPEN_REDIR "syntax error near unexpected token `{0}'\n"
#define LIT_NEWLINE "newline"

enum e_istoken
{
	IS_PIPE = 1,
	IS_REDIRECTION
};

/**
 * * Eval token to check between EOF, PIPE, REDIRECTION or NONE
 * @param token	token
 * @return 		token identiifcator
*/
static int	is_token(char *token)
{
	if (!token)
		return (EOF);
	else if (!ft_strcmp(token, "|"))
		return (IS_PIPE);
	else if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<") \
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (IS_REDIRECTION);
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
	if (is_token(*array) == IS_PIPE)
		error_near_token = ft_strdup(*array);
	while (*array != NULL && !error_near_token)
	{
		current = is_token(*array++);
		next = is_token(*array);
		if ((current == IS_REDIRECTION || current == IS_PIPE) && next == EOF)
			error_near_token = ft_strdup(LIT_NEWLINE);
		else if (current == IS_REDIRECTION && next != NONE)
			error_near_token = ft_strdup(*array);
		else if (current == IS_PIPE && next == IS_PIPE)
			error_near_token = ft_strdup(*array);
	}
	if (!error_near_token)
		return (0);
	log_error_free(ft_strreplace(OPEN_REDIR, "{0}", error_near_token), 258);
	free(error_near_token);
	return (1);
}

/**
 * * Returns token non redir type
 * @param token	token to identify
*/
int	eval_token_non_redir(const char *token)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(token, "cd") || !ft_strcmp(token, "echo") || \
	!ft_strcmp(token, "env") || !ft_strcmp(token, "exit") || \
	!ft_strcmp(token, "export") || !ft_strcmp(token, "pwd") || \
	!ft_strcmp(token, "unset"))
		return (BUILTIN);
	path = new_getpath((char *)token);
	if (path != NULL)
	{
		free(path);
		return (COMMAND);
	}
	return (TEXT);
}

/**
 * * Returns token redir type
 * @param token	token to identify
*/
int	eval_token_redir(const char *token)
{
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	else if (!ft_strcmp(token, "<"))
		return (INPUT_REDIRECT);
	else if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(token, ">"))
		return (OUPUT_REDIRECT);
	else if (!ft_strcmp(token, ">>"))
		return (APPENDS_OUTPUT_REDIRECT);
	return (NONE);
}

/**
 * * Eval if input has valid token to process
 * * Token is the minimun divisible item to handle on MiniShell
 * @param input	input to tokenize
 * @return		if input has valid token to process
*/
int	has_token(const char *input)
{
	while (ft_isspace(*input))
		input += 1;
	if (*input != '\0')
		return (TRUE);
	return (FALSE);
}
