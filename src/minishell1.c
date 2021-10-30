#include "minishell.h"
//#include <curses.h>
//#include <term.h>
//#include <termcap.h>
//#include <termios.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MINI "Minishell>"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		//rl_redisplay();

		printf(MINI);
		rl_replace_line("", 1);
		rl_newline(1, 1);
		rl_redisplay();
		// readline(MINI);
		//printf(MINI);
		//readline(MINI);
	}
}

int	main(void)
{
	char	*str_got;
	char	**param_list;
	int		i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	i = 0;
	while (1)
	{
		str_got = readline(MINI);
		//* No añadir entradas vacias
		if (*str_got != '\0') 
			add_history(str_got);
		param_list = modifsplit(str_got);
		interpreter(param_list);
		free(str_got);
	}
	write(1, "bye", 3);
	return (0);
}
