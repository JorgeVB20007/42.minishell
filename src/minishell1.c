#include "minishell.h"

/**
 * * Handle SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	ft_signal_handler(int signal)
{
	(void)signal;
	//TODO handle when there is some text
	write(1, MS_PROMPT_SIG_INT, ft_strlen(MS_PROMPT_SIG_INT));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void processline(void)
{
	char	*str_got;
	char	**param_list;

	str_got = readline(MS_PROMPT);
	if (str_got == NULL)
	{
		printf(MSG_EXIT_MINISHELL);
		exit(0);
	}
	if (*str_got != '\0')
	{
		add_history(str_got);
		if (!qm_error_detector(str_got) && has_token(str_got))
		{
			param_list = get_tokens(str_got);
			if (!has_pipe_redir_open(param_list))
				new_redirections(param_list, &g_env);
		}
		free(str_got);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_env = NULL;
	init_ms_env(env, &g_env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_signal_handler);
	while (1)
	{
		processline();
//		system("lsof -c minishell");
	}
	return (0);
}
