/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:54:05 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/09 12:27:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ENV_NOT_OPTIONS_ALLOWED  "Minishell's subject 'pwd with no options'\n"

/**
 * * This should recreate the bash funtion "pwd".
 * * Returms current working directory
 * @param env_list	enviroment list
 * @param argv		vector of arguments (ERROR if not null)
*/
void	ft_pwd(t_str **env_list, char **argv)
{
	char	cwd[PATH_MAX - 1];

	(void)env_list;
	if (argv[1] != NULL)
		printf(ENV_NOT_OPTIONS_ALLOWED);
	else
	{	
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		else
			printf("%s\n", cwd);
	}
}
