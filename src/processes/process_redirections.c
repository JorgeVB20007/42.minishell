/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:12:03 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/25 20:52:30 by jvacaris         ###   ########.fr       */
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

/*
?	This function is called to check if a file given as a parameter is valid
?	to write text in it. It checks if the file given corresponds to a 
?	directory or if the file doesn't have writing permissions. In this case, 
?	Minishell will return the corresponding error message and exit the 
?	execution of the current process with the exit code 1.
*/
static void	outputting_redirs(t_redirection *r, int *file)
{
	if ((!access(r->go_to, W_OK) && ft_is_directory(r->go_to)) || \
	access(r->go_to, F_OK))
	{
		if (r->type == OUPUT_REDIRECT)
			*file = open(r->go_to, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (r->type == APPENDS_OUTPUT_REDIRECT)
			*file = open(r->go_to, O_CREAT | O_WRONLY | O_APPEND, 0666);
		dup2(*file, STDOUT_FILENO);
	}
	else if (!ft_is_directory(r->go_to))
	{
		log_error_free(ft_strjoin(r->go_to, ": Is a directory\n"), 1);
		exit (1);
	}
	else
	{
		log_error_free(ft_strjoin(r->go_to, ": Permission denied\n"), 1);
		exit (1);
	}
}

/*
?	This function is called to check if a file given as a parameter is valid
?	to read text from it. It checks if the file given corresponds to a 
?	directory, if the file doesn't exist or lacks writing permissions. In 
?	this case, Minishell will return the corresponding error message and exit
?	the execution of the current process with the exit code 1.
*/
static void	inputting_redirs(t_redirection *r, int *file)
{
	if (r->type == INPUT_REDIRECT)
	{
		if (!access(r->go_to, R_OK) && ft_is_directory(r->go_to) && \
		!access(r->go_to, F_OK))
			*file = open(r->go_to, O_RDONLY, 0666);
		else
		{
			if (access(r->go_to, F_OK))
				log_error_free(ft_strjoin(r->go_to, \
				": No such file or directory\n"), 1);
			else if (access(r->go_to, R_OK))
				log_error_free(ft_strjoin(r->go_to, ": Permission denied\n"), 1);
			else
				log_error_free(ft_strjoin(r->go_to, ": Is a directory\n"), 1);
			exit (1);
		}
	}
	else
		*file = process_heredoc(r->go_to);
	dup2(*file, STDIN_FILENO);
}

void	process_redirections(t_redirection *r)
{
	int	file;

	file = 0;
	while (r != NULL)
	{
		if (r->type == OUPUT_REDIRECT || r->type == APPENDS_OUTPUT_REDIRECT)
		{
			outputting_redirs(r, &file);
		}
		else if (r->type == INPUT_REDIRECT || r->type == HEREDOC)
		{
			inputting_redirs(r, &file);
		}
		close(file);
		r = r->next;
	}
}
