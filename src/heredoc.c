/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:11:34 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/23 21:45:16 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Heredoc when quotation marks were found in *last_line*, so variables
*	don't expand.
*/
void	ft_heredoc_qm(int *fdi, char *last_line, int orig_fds[2])
{
	int		pip[2];
	char	*str_got;
	int		idx;
	pid_t	frk;
	int		status;

	pipe(pip);
	*fdi = pip[0];
	frk = fork();
	signal_handler_forks(!frk);
	if (!frk)
	{
		dup2(orig_fds[0], 0);
		dup2(orig_fds[1], 1);
		while (1)
		{
			idx = -1;
			str_got = readline("> ");
			if (str_got == NULL || !ft_strcmp(str_got, last_line))
				break ;
			while (str_got[++idx])
			{
				ft_putchar_fd(str_got[idx], pip[1]);
			}
			ft_putstr_fd("\n", pip[1]);
			free(str_got);
		}
		close(pip[1]);
		exit(0);
	}
	close(pip[1]);
	waitpid(frk, &status, 0);
}

/*
*	Heredoc when no quotation marks were found in *last_line*, so variables
*	expand properly.
*/
void	ft_heredoc(int *fdi, char *last_line, int orig_fds[2])
{
	int		pip[2];
	char	*str_got;
	int		idx;
	pid_t	frk;
	int		status;

	pipe(pip);
	*fdi = pip[0];
	frk = fork();
	signal_handler_forks(!frk);
	if (!frk)
	{
		dup2(orig_fds[0], 0);
		dup2(orig_fds[1], 1);
		while (1)
		{
			idx = -1;
			str_got = readline("> ");
			if (str_got == NULL || !ft_strcmp(str_got, last_line))
				break ;
			while (str_got[++idx])
			{
				if (is_valid_var_hd(str_got, idx))
				{
					ft_putstr_fd(ft_getenv(&str_got[++idx]), pip[1]);
					while (ft_isalnum(str_got[idx + 1]) || str_got[idx + 1] == '_')
						idx++;
				}
				else
					ft_putchar_fd(str_got[idx], pip[1]);
			}
			ft_putstr_fd("\n", pip[1]);
			free(str_got);
		}
		close(pip[1]);
		exit(0);
	}
	close(pip[1]);
	waitpid(frk, &status, 0);
}
