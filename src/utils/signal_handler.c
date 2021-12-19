#include "minishell.h"

/**
 * * Handles SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	signal_handler_default_sigint(int signal)
{
	(void)signal;
	write(1, MS_PROMPT_SIG_INT, ft_strlen(MS_PROMPT_SIG_INT));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * * Handles signals at forks, different behaviour between father and children
 * @param is_children	bool process is children
*/
void	signal_handler_forks(int is_children)
{
	signal(SIGQUIT, SIG_IGN);
	if (is_children == TRUE)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}

/**
 * * Handles signals out of forks
*/
void	signal_handler_default(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler_default_sigint);
}
