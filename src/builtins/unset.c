/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:09:09 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/06 20:32:46 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * This should recreate the bash funtion "unset".
 * * Remove enviroment record passed on argumment vector.
 * @param env_list	enviroment list
 * @param argv	vector of arguments containing records to remove
*/
void	ft_unset(t_str **env_list, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		ft_lst_str_delete(env_list, argv[i]);
		i++;
	}
}
