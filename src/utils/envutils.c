/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/10/31 19:28:27 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Get a default env
 * @param signal	signal identifier (see man signal)
*/
void	get_default_env(char **env)
{
	char	pwd[MAXPATHLEN];
	char	*pwd_command;

	pwd_command = NULL;
	getcwd(pwd, 100);
	env[0] = ft_strjoin("PWD=", pwd);
	env[1] = ft_strdup("SHLVL=1");
	pwd_command = ft_strjoin(pwd, "./minishell");
	env[2] = ft_strjoin("_=", pwd_command);
	env[3] = NULL;
	free(pwd_command);
}

/**
 * * Print ist of enviroment variables
 * @param env_list	list of enviroment variables
*/
void	print_env_list(char **env_list)
{
	int		i;

	i = 0;
	while (env_list[i] != 0)
		printf("%s\n", env_list[i]);
}
