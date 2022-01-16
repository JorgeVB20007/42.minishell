/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:13:37 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/16 06:55:13 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define WARNING_HEREDOC_EOF "Minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n"

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
		line_read = readline("> ");
		while (line_read == NULL)
		{
			printf(WARNING_HEREDOC_EOF, __LINE__, key);
			line_read = readline("> ");
		}
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
static char	*get_heredoc_pipedfork(const char *key)
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
	}
	waitpid(pid, &status, 0);
	signal_handler_default();
	if (WIFSIGNALED(status))
		return ((char *)key);
	return (ft_strdup(buff));
}

/**
 * * Get heredoc list from token list with open heredocs
 * @param token_list	token list to go through looking for open heredoc
 * 						to retrieve
 * @return				List of heredocs
*/
t_str	*get_heredoc_list(char **token_list)
{
	int		i;
	char	*heredoc;
	t_str	*heredoc_list;

	i = 0;
	heredoc_list = NULL;
	while (token_list[i] != NULL)
	{
		if (!ft_strcmp(token_list[i], "<<"))
		{
			heredoc = get_heredoc_pipedfork(token_list[i + 1]);
			if (!ft_strcmp(token_list[i + 1], heredoc))
			{
				lst_str_free(&heredoc_list);
				g_var.last_cmd_status = 130;
				break ;
			}
			if (!ft_strcmp(heredoc, ""))
			{
				free(heredoc);
				heredoc = NULL;
			}
			lst_str_add_back(&heredoc_list, heredoc);
		}
		i++;
	}
	return (heredoc_list);
}
