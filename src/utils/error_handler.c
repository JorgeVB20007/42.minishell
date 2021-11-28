#include "minishell.h"

void	log_error(char *str_error, int errno)
{
	ft_putstr(MS_EROR, STDERR_FILENO);
	ft_putstr(str_error, STDERR_FILENO);
	g_var.status = errno;
}
