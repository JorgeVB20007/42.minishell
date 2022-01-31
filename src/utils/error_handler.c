/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:13:58 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/31 15:29:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MS_ERROR "Minishell: "
#define ULTIMATE_QUESTION_LIFE_ANSWER 42

/**
 * * Log error into STDERR_FILENO & set catched status error
 * @param str_error		Error to log into STDERR_FILENO
 * @param status_error	status error to set
*/
void	log_error(char *str_error, int status_error)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd(str_error, STDERR_FILENO);
	g_var.current_status = status_error;
}

/**
 * * Log error into STDERR_FILENO & set catched status error
 * * Free malloc log error input
 * @param malloc_str_error	Error to log into STDERR_FILENO
 * @param status_error	status error to set
*/
void	log_error_free(char *malloc_str_error, int status_error)
{
	log_error(malloc_str_error, status_error);
	free(malloc_str_error);
}

void	execve_sleep(char **sleep_argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(sleep_argv[0], &sleep_argv[1], NULL);
	waitpid(pid, &status, 0);
}

/**
 * * Count amount of pipes present in tokens
 * @param tokens	tokens list
*/
int	count_pipes(char **tokens)
{
	int		pipes;

	pipes = 0;
	while (*tokens != NULL && pipes < INT_MAX)
		if (!ft_strcmp(*tokens++, "|"))
			pipes++;
	return (pipes);
}

/**
 * * This returns eight module of ramdon number between ZERO and RAND_MAX
 * @param str	optional str
*/
int	ft_rand_eight_module(const char *str)
{
	size_t	nbr;

	nbr = 0;
	if (str != NULL)
		nbr = ft_strlen(str);
	g_var.rng += ULTIMATE_QUESTION_LIFE_ANSWER + nbr;
	if (g_var.rng % 3 == 0)
		g_var.rng++;
	if (g_var.rng > RAND_MAX)
		g_var.rng >>= 24;
	nbr = g_var.rng;
	return (nbr % 8);
}
