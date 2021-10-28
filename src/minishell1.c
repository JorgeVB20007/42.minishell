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
		str_got = readline("\033[0;34mMinishell\033[0;31m>\033[0;37m");
		add_history(str_got);
		param_list = modifsplit(str_got);
		interpreter(param_list);
	}
	write(1, "bye", 3);
	return (0);
}
