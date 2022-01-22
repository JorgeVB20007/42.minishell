#include "minishell.h"

#define MS_ERROR "Minishell: "

/**
 * * Log error into STDERR_FILENO & set catched status error
 * @param str_error		Error to log into STDERR_FILENO
 * @param status_error	status error to set
*/
void	log_error(char *str_error, int status_error)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd(str_error, STDERR_FILENO);
	g_var.last_cmd_status = status_error;
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
