/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:09:09 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/28 20:11:03 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define UNSET_WRONG_ID "unset: `{0}': not a valid identifier\n"

/**
 * * Evals vallid export to add
 * @param str	enviroment list
*/
static int	is_valid_add_unset(const char *str)
{
	char	*aux;
	int		has_like;
	int		ok;

	aux = (char *)str;
	has_like = 0;
	ok = ft_isalpha(*aux++);
	while (*aux != '\0' && !has_like && ok == 1)
	{
		if (!ft_isalnum(*aux) && !ft_strchr("=\"", *aux))
			ok = 0;
		if (*aux == '=')
			has_like = 1;
		aux++;
	}
	--aux;
	if (!ok)
		log_error_free(ft_strreplace(UNSET_WRONG_ID, "{0}", str), 1);
	return (ok);
}

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
		if (is_valid_add_unset(argv[i]))
			lst_str_delete(env_list, argv[i], ft_strlen(argv[i]));
		i++;
	}
}
