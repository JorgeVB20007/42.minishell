/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 08:33:14 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/29 15:39:02 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Redirect to proper builtin
 * @param argv		arguments vector
*/
void	ft_builtins(char **argv)
{
	if (!ft_strcmp(*argv, "cd"))
		ft_cd(argv);
	else if (!ft_strcmp(*argv, "echo"))
		ft_echo(argv);
	else if (!ft_strcmp(*argv, "exit"))
		ft_exit(argv);
	else if (!ft_strcmp(*argv, "export"))
		ft_export(argv);
	else if (!ft_strcmp(*argv, "env"))
		ft_env(argv);
	else if (!ft_strcmp(*argv, "pwd"))
		ft_pwd(argv);
	else if (!ft_strcmp(*argv, "unset"))
		ft_unset(argv);
}
