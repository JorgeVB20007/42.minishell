#include "minishell.h"
//#include <curses.h>
//#include <term.h>
//#include <termcap.h>
//#include <termios.h>

int	main(void)
{
	char	*test;

//	test = calloc(1, 1);
	while (1)
	{
		test = readline("\033[0;34mMinishell\033[0;31m>\033[0;37m");
		add_history(test);
		write(1, test, 2);
		write(1, "\n", 2);
	}
	write(1, "bye", 3);
	return (0);
}
