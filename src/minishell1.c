#include "minishell.h"
//#include <curses.h>
//#include <term.h>
//#include <termcap.h>
//#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*test;

	while (1)
	{
		test = readline("\033[0;34mMinishell\033[0;31m>\033[0;37m");
		add_history(test);
		modifsplit(test);
	}
	write(1, "bye", 3);
	return (0);
}
