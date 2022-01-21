/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:56:38 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/21 22:43:35 by emadriga         ###   ########.fr       */
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
	path = new_getpath((char *)token, &g_var.env);
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
 * * Returns token type
 * @param token	token to identify
*/
int	eval_token(const char *token)
{
	int		out;
	char	*aux;

	out = eval_token_redir(token);
	if (out != NONE)
		return (out);
	aux = adv_qm_rem((char *)token, FALSE);
	out = eval_token_non_redir(aux);
	free(aux);
	return (out);
}
