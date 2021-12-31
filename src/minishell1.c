#include "minishell.h"

# define CARRIAGE_RETURN "\033[AMinishell> "
# define MSG_EXIT_MINISHELL "exit\n"
# define MS_PROMPT "Minishell> "

/**
 * * Disables CTRL hotkey(+c) from printing ^C 
*/
static void	disable_ctrl_c_hotkey(void)
{
	struct termios	termios;
	int				rc;

	rc = tcgetattr(0, &termios);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}

/**
 * * Process every input line sended on STDIN_FILENO
 * @param ignored_env	boolean to emulate bash CTRL hotkey(+d)(exit) depending
 *  on env was ignored at start of the program
*/
static void	processline(int ignored_env)
{
	char	*str_got;
	char	**param_list;

	str_got = readline(MS_PROMPT);
	if (str_got == NULL)
	{
		if (ignored_env == FALSE)
			printf(CARRIAGE_RETURN);
		lst_str_free(&g_var.env);
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
				new_redirections(param_list, &g_var.env);
		}
		free(str_got);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_var.env = NULL;
	g_var.last_cmd_status = 0;
	disable_ctrl_c_hotkey();
	init_ms_env(env, &g_var.env);
	while (1)
	{
		signal_handler_default();
		processline(env[0] == NULL);
//		system("lsof -c minishell");
	}
	return (0);
}
