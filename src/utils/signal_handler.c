/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:58:37 by emadriga          #+#    #+#             */
/*   Updated: 2022/02/08 21:58:22 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SIGQUIT_MSG "Quit:"

/**
 * * Handles SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	signal_handler_default_sigint(int signal)
{
	(void)signal;
	g_var.last_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
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
	if (is_child == TRUE)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}

/**
 * * Handles signals out of forks
*/
void	signal_handler_default(void)
{
	g_var.elephants = PLAYING;
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
	g_var.elephants = PUNISHED;
}

/**
 * * Handles SIGINT signal CTRL+C, exit process
 * @param signal	signal identifier (see man signal)
*/
void	signal_handler_process_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_var.current_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (signal == SIGQUIT)
	{
		g_var.current_status = 131;
		ft_putstr_fd(SIGQUIT_MSG, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
