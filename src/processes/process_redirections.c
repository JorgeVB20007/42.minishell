/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:12:03 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/24 22:34:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc(const char	*str)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	signal_handler_forks(!pid);
	if (!pid)
	{
		close(pipe_fd[READ_END]);
		write(pipe_fd[WRITE_END], str, ft_strlen(str));
		write(pipe_fd[WRITE_END], "\n", 1);
		close(pipe_fd[WRITE_END]);
		exit(0);
	}
	close(pipe_fd[WRITE_END]);
	waitpid(pid, &status, 0);
	return (pipe_fd[READ_END]);
}

void	process_redirections(t_redirection *r)
{
	int	file;

	while (r != NULL)
	{
		if (r->type == OUPUT_REDIRECT || r->type == APPENDS_OUTPUT_REDIRECT)
		{
			if (r->type == OUPUT_REDIRECT)
				file = open(r->go_to, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (r->type == APPENDS_OUTPUT_REDIRECT)
				file = open(r->go_to, O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(file, STDOUT_FILENO);
		}
		else if (r->type == INPUT_REDIRECT || r->type == HEREDOC)
		{
			if (r->type == INPUT_REDIRECT)
				file = open(r->go_to, O_RDONLY, 0666);
			if (r->type == HEREDOC)
				file = process_heredoc(r->go_to);
			dup2(file, STDIN_FILENO);
		}
		close(file);
		r = r->next;
	}
}
