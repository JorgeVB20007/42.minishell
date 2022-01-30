/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:52:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/30 18:48:14 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define UNEXPECTED_EOF "unexpected EOF while looking for matching `{0}'\n\
Minishell: syntax error: unexpected end of file\n"
#define BACKSLASH 3

/**
 * * Eval if a given string has open quotes returning NONE if doesn't
 * * and SINGLE or DOUBLE depending on the openquote
 * @param str	string to eval
*/
static int	has_open_quotes(char *str)
{
	int	open_quotes;

	open_quotes = NONE;
	if (*str == '\0')
		return (open_quotes);
	while (*str != '\0')
	{
		if (open_quotes == NONE && *str == '\'')
			open_quotes = SINGLE;
		else if (open_quotes == SINGLE && *str == '\'')
			open_quotes = NONE;
		else if (open_quotes == NONE && *str == '\"')
			open_quotes = DOUBLE;
		else if (open_quotes == DOUBLE && *str == '\"')
			open_quotes = NONE;
		str++;
	}
	if (open_quotes == NONE && str[-1] == '\\')
		return (BACKSLASH);
	return (open_quotes);
}

/**
 * * Handle unclosed quotes waiting STDIN_FILENO to close them
 * @param str	current STDIN_FILENO input
*/
static char	*recursive_close_quotes(char *str)
{
	int		open_quotes;
	char	*out;
	char	*line_read;

	out = str;
	open_quotes = has_open_quotes(str);
	if (open_quotes != NONE)
	{
		line_read = readline("> ");
		if (line_read == NULL)
		{
			free(str);
			exit (open_quotes);
		}
		if (open_quotes == BACKSLASH)
			out = recursive_close_quotes(ft_strjoin_freedouble(str, line_read));
		else
			out = recursive_close_quotes(ft_strjoin_freedouble(str, \
				ft_strjoin_freedouble(ft_strdup("\n"), line_read)));
	}
	return (out);
}

/**
 * * Piped fork child child refresh input to send it to father
 * @param str		current STDIN_FILENO input
 * @param pipe_fd	pipe's file descriptors
*/
static char	*close_quotes_pipedfork_child(char *str, int *pipe_fd)
{
	char	*out;

	close(pipe_fd[READ_END]);
	out = recursive_close_quotes(ft_strdup(str));
	write(pipe_fd[WRITE_END], out, ft_strlen(out));
	close(pipe_fd[WRITE_END]);
	free (out);
	exit(0);
}

static int	w_ifsignaled_ifexitstatus(int status)
{
	if (WIFSIGNALED(status))
		g_var.current_status = 130;
	else if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		if (WEXITSTATUS(status) == SINGLE)
			log_error_free(ft_strreplace(UNEXPECTED_EOF, "{0}", "\'"), 2);
		else if (WEXITSTATUS(status) == DOUBLE)
			log_error_free(ft_strreplace(UNEXPECTED_EOF, "{0}", "\""), 2);
	}
	return (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status)));
}

/**
 * * Piped fork to handle unclosed quotes with signals without shuting MS
 * * child refresh input str with new STDIN_FILENO input
 * * father waits for child response or sigint
 * @param key	key to match with STDIN_FILENO
*/
char	*close_quotes_pipedfork(char *str)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	char	buff[SHRT_MAX];

	ft_memset(buff, '\0', SHRT_MAX);
	pipe(pipe_fd);
	pid = fork();
	signal_handler_forks(!pid);
	if (!pid)
		close_quotes_pipedfork_child(str, pipe_fd);
	else
	{
		close(pipe_fd[WRITE_END]);
		read(pipe_fd[READ_END], buff, SHRT_MAX);
		close(pipe_fd[READ_END]);
	}
	free(str);
	waitpid(pid, &status, 0);
	signal_handler_default();
	if (w_ifsignaled_ifexitstatus(status))
		return (ft_strdup("\0"));
	return (ft_strdup(buff));
}
