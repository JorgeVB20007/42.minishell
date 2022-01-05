/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:52:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/05 21:37:18 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Eval if a given string has open quotes returning NONE if doesn't
 * * and SINGLE or DOUBLE depending on the openquote
 * @param str	string to eval
*/
static int	has_open_quotes(char *str)
{
	int	open_quotes;

	open_quotes = NONE;
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
			exit (1);
		}
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

/**
 * * Piped fork to handle unclosed quotes  with signals without shuting MS
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
	}
	free(str);
	waitpid(pid, &status, 0);
	signal_handler_default();
	if (WIFEXITED(status) && WEXITSTATUS(status))
		log_error(UNEXPECTED_EOF, 2);
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status)))
		return ("\0");
	return (ft_strdup(buff));
}
