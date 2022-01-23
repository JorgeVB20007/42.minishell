/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:09:09 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/23 08:23:42 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * This should recreate the bash funtion "unset".
 * * Remove enviroment record passed on argumment vector.
 * @param env_list	enviroment list
 * @param argv	vector of arguments containing records to remove
*/
void	ft_unset(char **argv)
{
	int		i;
	t_str	**env_list;

	i = 1;
	env_list = &g_var.env;
	while (argv[i] != NULL)
	{
		lst_str_delete(env_list, argv[i], ft_strlen(argv[i]));
		i++;
	}
}
