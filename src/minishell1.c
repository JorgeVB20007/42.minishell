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

int	main(int argc, char **argv, char **env)
{
	char	*str_got;
	char	**param_list;
	t_str	*env_list;

	(void)argc;
	(void)argv;
//	printf("\nhye\n");
	env_list = NULL;
	init_ms_env(env, &env_list);
//	ft_pwd();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_signal_handler);
	while (1)
	{
		str_got = readline(MS_PROMPT);
		if (str_got == NULL)
		{
			printf(MSG_EXIT); //TODO write exit at console input's level
			exit(0);
		}
		if (*str_got != '\0' )
			add_history(str_got);
		if (qm_error_detector(str_got))
			write(1, "Error: quotation marks not properly closed!\n", 44);
		else
		{
			param_list = modifsplit(str_got);
			interpreter(param_list, &env_list);
		}
		free(str_got);
//		system("lsof -c minishell");
	}
	return (0);
}

