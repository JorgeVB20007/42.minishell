#include "minishell.h"

#define MS_ERROR "Minishell: "

void	log_error(char *str_error, int status_error)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd(str_error, STDERR_FILENO);
	g_var.last_cmd_status = status_error;
}

void	log_error_free(char *malloc_str_error, int status_error)
{
	log_error(malloc_str_error, status_error);
	free(malloc_str_error);
}
