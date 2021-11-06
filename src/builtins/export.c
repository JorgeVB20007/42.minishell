/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:42:55 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/06 20:42:57 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * This should recreate the bash funtion "export".
 * * Returns ENV alphabetically-sorted  
 * * Add records (through argumment vector) to enviroment variables list
 * @param env_list	enviroment list
 * @param argv	vector of arguments containing records to add
*/
<<<<<<< HEAD
/*void	ft_export(t_str *env_list, char * record)
=======
void	ft_export(t_str **env_list, char **argv)
>>>>>>> master
{
	int		i;
	char	*env_desc;
	char	*strchr_n;

	i = 1;
	env_desc = NULL;
<<<<<<< HEAD
	env_desc = ft_substr(*record, 0, ft_strchr(*record, '=') - *record + 1);
	//TODO Log with errors and locations (function throwing them) 'd be great
	ft_lst_str_delete(env_list, env_desc);
	ft_lstadd_front(env_list, record); //record should came with malloc
}*/
=======
	if (argv[i] == NULL)
		ft_lst_str_print(*env_list);
	while (argv[i] != NULL)
	{
		strchr_n = ft_strchr(argv[i], '=');
		if (strchr_n)
			env_desc = ft_substr(argv[i], 0, strchr_n - argv[i] + 1);
		else
			env_desc = ft_strdup(argv[i]);
		ft_lst_str_delete(env_list, env_desc);
		ft_lst_str_add_sorted(env_list, argv[i]);
		free(env_desc);
		i++;
	}
}
>>>>>>> master
