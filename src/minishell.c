/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:18:08 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/28 17:49:42 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CARRIAGE_RETURN "\033[AMinishell> "
#define MSG_EXIT_MINISHELL "exit\n"
#define MS_PROMPT "Minishell> "
#define ERROR_DOT ".: filename argument required\n\
.: usage: . filename [arguments]\n"
#define ERROR_DOTS "..: command not found\n"

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
 * * Exits from MS (EOF received on readline)
 * @param ignored_env	boolean to emulate bash CTRL hotkey(+d)(exit) depending
 *  on env was ignored at start of the program
*/
static void	ms_eof_exit(int ignored_env)
{
	if (ignored_env == FALSE)
		printf(CARRIAGE_RETURN);
	lst_str_free(&g_var.env);
	printf(MSG_EXIT_MINISHELL);
	exit(0);
}

/**
 * * Process every input line sended on STDIN_FILENO
 * @param line_read	line read from STDIN_FILENO
*/
static void	processline(char *line_read)
{
	char	**token_list;
	t_p		*processes;

	processes = NULL;
	line_read = close_quotes_pipedfork(line_read);
	if (*line_read != '\0')
	{
		add_history(line_read);
		if (!qm_error_detector(line_read) && has_token(line_read))
		{
			token_list = get_token_list(line_read);
			if (token_list != NULL && !has_pipe_redir_open(token_list))
			{
				get_processes(token_list, &processes);
				if (!g_var.current_status)
					run_processes(&processes, count_pipes(token_list) + 1);
			}
			lst_process_free(&processes);
			megafree(&token_list);
		}
		ft_rand(line_read);
	}
	ft_free((void **)&line_read);
}

static char *pre_process_line(int ignored_env)
{
	char	*line_read;
	char	*out;

	line_read = NULL;
	out = NULL;
	line_read = readline(MS_PROMPT);
	if (line_read == NULL)
		ms_eof_exit(ignored_env);
	else if (!ft_strcmp(line_read, "."))
		log_error(ERROR_DOT, 2);
	else if (!ft_strcmp(line_read, ".."))
		log_error(ERROR_DOTS, 127);
	else
		out = ft_strdup(line_read);
	ft_free((void **)&line_read);
	return (out);
}

int	main(int argc, char **argv, char **env)
{
	char	*line_read;

	(void)argc;
	(void)argv;
	line_read = NULL;
	g_var.env = NULL;
	g_var.current_status = NONE;
	g_var.last_status = NONE;
	g_var.rng = 0;
	disable_ctrl_c_hotkey();
	init_ms_env(env, &g_var.env);
	while (1)
	{
		signal_handler_default();
		line_read = pre_process_line(env[0] == NULL);
		if (line_read != NULL)
			processline(line_read);
		g_var.last_status = g_var.current_status;
//		system("leaks minishell");
	}
	return (0);
}
