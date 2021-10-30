#include "minishell.h"
//#include <curses.h>
//#include <term.h>
//#include <termcap.h>
//#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*str_got;
	char	**param_list;

	while (1)
	{
		str_got = readline("Minishell> ");
		if (*str_got != '\0')
			add_history(str_got);
		if (qm_error_detector(str_got))
			write(1, "Error: quotation marks not properly closed!\n", 44);
		else
		{
			param_list = modifsplit(str_got);
			interpreter(param_list);
		}
	}
	write(1, "bye", 3);
	return (0);
}
