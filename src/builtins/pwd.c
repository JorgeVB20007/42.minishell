/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:54:05 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/23 08:22:50 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ENV_NOT_OPTIONS_ALLOWED  "Minishell's subject 'pwd with no options'\n"

/**
 * * This should recreate the bash funtion "pwd".
 * * Returms current working directory
 * @param argv		vector of arguments (ERROR if not null)
*/
void	ft_pwd(char **argv)
{
	char	cwd[PATH_MAX];

	if (argv[1] != NULL && argv[1][0] != '|' && argv[1][0] != '<' \
	&& argv[1][0] != '>')
		log_error(ENV_NOT_OPTIONS_ALLOWED, 1);
	else
	{
		getcwd(cwd, PATH_MAX);
		printf("%s\n", cwd);
	}
}
