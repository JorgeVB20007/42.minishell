/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/01 15:07:19 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Get a default env
 * @param signal	signal identifier (see man signal)
*/
// static void	get_default_env(char **env)
// {
// 	char	pwd[MAXPATHLEN];
// 	char	*pwd_command;

// 	pwd_command = NULL;
// 	getcwd(pwd, 100);
// 	env[0] = ft_strjoin("PWD=", pwd);
// 	env[1] = ft_strdup("SHLVL=1");
// 	pwd_command = ft_strjoin(pwd, "./minishell");
// 	env[2] = ft_strjoin("_=", pwd_command);
// 	env[3] = NULL;
// 	free(pwd_command);
// }

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

//void	ft_lstiter(t_list *lst, void (*f)(void *))
/**
 * * Initialize minishel enviroment variables list from input list
 * @param env_vector	input enviroment vector at exec ./minishell
 * @param env_list	output enviroment list returned
*/
void	init_ms_env(char **env_vector, t_str **env_list)
{
	int		i;

	i = 0;
	while (env_vector[i] != 0)
	{
		ft_lstadd_back_str(env_list, ft_strdup(env_vector[i]));
		i++;
	}
	ft_printlist_str(*env_list);
}
