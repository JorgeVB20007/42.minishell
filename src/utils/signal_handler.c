#include "minishell.h"

/**
 * * Handle SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	signal_handler_default_sigint(int signal)
{
	(void)signal;
	//TODO handle when there is some text
	write(1, MS_PROMPT_SIG_INT, ft_strlen(MS_PROMPT_SIG_INT));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_forks(int is_children)
{
	signal(SIGQUIT, SIG_IGN);
	if (is_children == TRUE)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}

void	signal_handler_default(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler_default_sigint);
}
