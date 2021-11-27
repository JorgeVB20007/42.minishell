/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:11:34 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/27 17:24:31 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Heredoc when quotation marks were found in *last_line*, so variables
*	don't expand.
*/
void	ft_heredoc_qm(int *fdi, char *last_line)
{
	int		pip[2];
	char	*str_got;

	pipe(pip);
	*fdi = pip[0];
	while (1)
	{
		str_got = readline("> ");
		if (!modstrcmp(str_got, last_line) || str_got == NULL)
			break ;
		ft_putstr_fd(str_got, pip[1]);
		ft_putstr_fd("\n", pip[1]);
		free(str_got);
	}
	close(pip[1]);
	dup2(*fdi, 0);
}

/*
*	Heredoc when no quotation marks were found in *last_line*, so variables
*	expand properly.
*/
void	ft_heredoc(int *fdi, char *last_line)
{
	int		pip[2];
	char	*str_got;
	int		idx;

	pipe(pip);
	*fdi = pip[0];
	while (1)
	{
		idx = -1;
		str_got = readline("> ");
		if (!modstrcmp(str_got, last_line) || str_got == NULL)
			break ;
		while (str_got[++idx])
		{
			if (is_valid_var_hd(str_got, idx))
			{
				//ft_putstr_fd(getvarvalue(&str_got[++idx]), pip[1]);
				ft_putstr_fd(ft_getenv(&g_env, &str_got[++idx]), pip[1]);
				while (ft_isalnum(str_got[idx]) || str_got[idx] == '_')
					idx++;
			}
			else
				ft_putchar_fd(str_got[idx], pip[1]);
		}
		ft_putstr_fd("\n", pip[1]);
		free(str_got);
	}
	close(pip[1]);
}
