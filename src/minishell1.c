#include "minishell.h"

#define CARRIAGE_RETURN "\033[AMinishell> "
#define MSG_EXIT_MINISHELL "exit\n"
#define MS_PROMPT "Minishell> "
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
	char	*line_read;
	char	**token_list;

	line_read = readline(MS_PROMPT);
	if (line_read == NULL)
	{
		if (ignored_env == FALSE)
			printf(CARRIAGE_RETURN);
		lst_str_free(&g_var.env);
		printf(MSG_EXIT_MINISHELL);
		exit(0);
	}
	line_read = close_quotes(line_read);
	printf("Received str -> %s\n", line_read);
	if (*line_read != '\0')
	{
		add_history(line_read);
		if (!qm_error_detector(line_read) && has_token(line_read))
		{
			token_list = get_token_list(line_read);
			get_heredoc_list(token_list);
			if (token_list != NULL && !has_pipe_redir_open(token_list))
				new_redirections(token_list, &g_var.env);
		}
		free(line_read);
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
