/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:13:37 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/30 19:14:00 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define WARNING_HEREDOC_EOF "Minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n"

static char	*get_readline_heredoc(const char *key)
{
	char	*line_read;
	char	*out;

	line_read = readline("> ");
	out = ft_strdup("");
	while (1)
	{
		while (line_read == NULL)
		{
			printf(WARNING_HEREDOC_EOF, __LINE__, key);
			line_read = readline("> ");
		}
		out = ft_strjoin_freedouble(out, line_read);
		if (*out != '\0' && out[ft_strlen(out) - 1] == '\\')
			line_read = readline("> ");
		else
			break ;
	}
	return (out);
}

/**
 * * Get matching key heredoc from STDIN_FILENO
 * @param key	key to match with STDIN_FILENO
*/
static char	*get_heredoc(const char *key)
{
	char	*line_read;
	char	*out;

	out = ft_strdup("");
	while (1)
	{
		line_read = get_readline_heredoc(key);
		if (!ft_strcmp(key, line_read))
			break ;
		if (!ft_strcmp(out, ""))
			out = ft_strjoin_freedouble(out, line_read);
		else
			out = ft_strjoin_freedouble(out, \
			ft_strjoin_freedouble(ft_strdup("\n"), line_read));
	}
	if (line_read != NULL)
		free(line_read);
	return (out);
}

/**
 * * Piped fork child retrieves heredoc to send it to father
 * @param key		key to match with STDIN_FILENO
 * @param pipe_fd	pipe's file descriptors
*/
static void	get_heredoc_pipedfork_child(const char *key, int *pipe_fd)
{
	char		*out;

	close(pipe_fd[READ_END]);
	out = get_heredoc(key);
	write(pipe_fd[WRITE_END], out, ft_strlen(out));
	close(pipe_fd[WRITE_END]);
	free(out);
	exit(0);
}

/**
 * * Piped fork to handle signals without shuting MS
 * * child retrieves heredoc
 * * father waits for child response or sigint
 * @param key	key to match with STDIN_FILENO
*/
char	*get_heredoc_pipedfork(const char *key)
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
		get_heredoc_pipedfork_child(key, pipe_fd);
	else
	{
		close(pipe_fd[WRITE_END]);
		read(pipe_fd[READ_END], buff, SHRT_MAX);
		close(pipe_fd[READ_END]);
	}
	waitpid(pid, &status, 0);
	signal_handler_default();
	if (WIFSIGNALED(status))
		return (ft_strdup(key));
	return (ft_strdup(buff));
}

/**
 * * Get heredoc list from token list with open heredocs
 * @param token_list	token list to go through looking for open heredoc
 * 						to retrieve
 * @param heredoc_list	List of heredocs to return
*/
void	get_heredoc_list(char **token_list, t_str **heredoc_list)
{
	int		i;
	char	*heredoc;

	i = 0;
	while (token_list[i] != NULL)
	{
		if (!ft_strcmp(token_list[i], "<<"))
		{
			heredoc = get_heredoc_pipedfork(token_list[i + 1]);
			if (!ft_strcmp(heredoc, ""))
			{
				free(heredoc);
				heredoc = NULL;
			}
			lst_str_add_back(heredoc_list, heredoc);
			if (heredoc != NULL && !ft_strcmp(token_list[i + 1], heredoc))
			{
				lst_str_free(heredoc_list);
				g_var.current_status = 130;
				break ;
			}
		}
		i++;
	}
}
