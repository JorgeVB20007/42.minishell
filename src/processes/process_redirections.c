/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:12:03 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/29 17:41:37 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define AMBIGUOS_REDIR "{0}: ambiguous redirect\n"
#define NOT_PERMISSION "{0}: Permission denied\n"
#define IS_DIRECTORY "{0}: Is a directory\n"
#define NOT_EXITS "{0}: No such file or directory\n"

/**
 * * Handle process heredoc 
 * @param str		heredoc content
*/
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
		if (str != NULL)
		{
			write(pipe_fd[WRITE_END], str, ft_strlen(str));
			write(pipe_fd[WRITE_END], "\n", 1);
		}
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
static void	outputting_redirs(const char *str, int *file, int redirection_type)
{
	char	*error;

	error = NULL;
	if (!ft_is_directory(str) && !access(str, F_OK))
		error = ft_strreplace(IS_DIRECTORY, "{0}", str);
	else if (access(str, W_OK) && !access(str, F_OK))
		error = ft_strreplace(NOT_PERMISSION, "{0}", str);
	if (error != NULL)
	{
		log_error_free(error, 1);
		exit(1);
	}
	if (redirection_type == OUPUT_REDIRECT)
		*file = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (redirection_type == APPENDS_OUTPUT_REDIRECT)
		*file = open(str, O_CREAT | O_WRONLY | O_APPEND, 0666);
	dup2(*file, STDOUT_FILENO);
}

/*
?	This function is called to check if a file given as a parameter is valid
?	to read text from it. It checks if the file given corresponds to a
?	directory, if the file doesn't exist or lacks writing permissions. In
?	this case, Minishell will return the corresponding error message and exit
?	the execution of the current process with the exit code 1.
*/
static void	inputting_redirs(const char *str, int *file)
{
	char	*error;

	error = NULL;
	if (access(str, F_OK))
		error = ft_strreplace(NOT_EXITS, "{0}", str);
	else if (access(str, R_OK))
		error = ft_strreplace(NOT_PERMISSION, "{0}", str);
	else if (!ft_is_directory(str))
		error = ft_strreplace(IS_DIRECTORY, "{0}", str);
	if (error != NULL)
	{
		log_error_free(error, 1);
		exit(1);
	}
	*file = open(str, O_RDONLY, 0666);
	dup2(*file, STDIN_FILENO);
}

/**
 * * Expand process redirection 
 * @param r		process redirection
*/
static char	*expand_redirection(t_redirection *r)
{
	char	*str;

	str = adv_qm_rem(ft_expand(r->go_to), FREE);
	if (!ft_strcmp(str, "\0"))
	{
		log_error_free(ft_strreplace(AMBIGUOS_REDIR, "{0}", r->go_to), 1);
		exit(1);
	}
	return (str);
}

/**
 * * Handle process redirections 
 * @param r		process redirection
*/
void	process_redirections(t_redirection *r)
{
	int		file;
	char	*str;

	file = 0;
	while (r != NULL)
	{
		if (r->type != HEREDOC)
			str = expand_redirection(r);
		if (r->type == OUPUT_REDIRECT || r->type == APPENDS_OUTPUT_REDIRECT)
			outputting_redirs(str, &file, r->type);
		else if (r->type == INPUT_REDIRECT)
			inputting_redirs(str, &file);
		else if (r->type == HEREDOC)
		{
			file = process_heredoc(r->go_to);
			dup2(file, STDIN_FILENO);
		}
		close(file);
		if (r->type != HEREDOC)
			free(str);
		r = r->next;
	}
}
