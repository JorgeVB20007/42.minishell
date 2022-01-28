/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:58:37 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/28 17:51:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Handles SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	signal_handler_default_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * * Handles signals at forks, different behaviour between father and children
 * @param is_child	bool process is children
*/
void	signal_handler_forks(int is_child)
{
	signal(SIGINT, SIG_DFL);
	if (is_child == TRUE)
	{
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

/**
 * * Handles signals out of forks
*/
void	signal_handler_default(void)
{
	g_var.elephants = FALSE;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler_default_sigint);
}

/**
 * * Handles SIGINT signal CTRL+C, end simulation
 * @param signal	signal identifier (see man signal)
*/
void	signal_handler_elephants_sigint(int signal)
{
	(void)signal;
	g_var.elephants = TRUE;
}

/**
 * * Handles SIGINT signal CTRL+C, exit process
 * @param signal	signal identifier (see man signal)
*/
void signal_handler_process_sigint(int signal)
{
	(void)signal;
	g_var.current_status = 130;
	exit(g_var.current_status);
}

