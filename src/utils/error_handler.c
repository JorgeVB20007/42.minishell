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
