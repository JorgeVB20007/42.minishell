#include "minishell.h"
#define EXIT_NUM_REQUIRED "exit: {0}: numeric argument required\n"
#define EXIT_ARG_EXCEEDED "exit: too many arguments\n"
#define EXIT_MAX_INPUT_LEN 19

/**
 * * Return exit status from a number given
 * * 0 is returned for bigger numbers than INT_MAX
 * @param str_nbr	string number to get exit status
*/
static int	get_exit_status(const char *str_nbr)
{
	unsigned int	result;

	result = 0;
	while (*str_nbr >= '0' && *str_nbr <= '9' && result < INT_MAX)
		result = 10 * result + (int)(*str_nbr++ - '0');
	if (result > INT_MAX)
		result = 0;
	return (result % 256);
}

/**
 * * This should recreate the bash funtion "exit".
 * * Causes normal process termination and the status is returned
 * @param argv	vector of arguments
*/
void	ft_exit(char **argv)
{
	int		i;

	if (argv[1] == NULL)
		exit(EXIT_SUCCESS);
	i = 0;
	while (ft_isdigit(argv[1][i]))
		i++;
	if (argv[1][i] != '\0' || i > EXIT_MAX_INPUT_LEN)
		log_error_free(ft_strreplace(EXIT_NUM_REQUIRED, "{0}", argv[1]), 255);
	else if (argv[2] != NULL)
	{
		log_error(EXIT_ARG_EXCEEDED, 1);
		return ;
	}
	else
		g_var.current_status = get_exit_status(argv[1]);
	lst_str_free(&g_var.env);
	exit(g_var.current_status);
}
