/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:17:59 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/29 17:39:26 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXPAND_HOME "$HOME"
#define EXPAND_PWD "$PWD"
#define EXPAND_OLDPWD "$OLDPWD"

char	*expanse_tilde(const char *str)
{
	char	*aux;
	t_str	*env;

	aux = NULL;
	env = NULL;
	if (!ft_strcmp(str, "~") || !ft_strncmp(str, "~/", 2))
		aux = ft_strreplaceat(str, "~", EXPAND_HOME, 0);
	else if (!ft_strcmp(str, "~+") || !ft_strncmp(str, "~+/", 3))
	{
		env = lst_str_get_str(&g_var.env, LIT_PWD_LIKE);
		if (!aux && env != NULL)
			aux = ft_strreplaceat(str, "~+", EXPAND_PWD, 0);
	}
	else if (!ft_strcmp(str, "~-") || !ft_strncmp(str, "~-/", 3))
	{
		env = lst_str_get_str(&g_var.env, LIT_OLDPWD_LIKE);
		if (!aux && env != NULL)
			aux = ft_strreplaceat(str, "~-", EXPAND_OLDPWD, 0);
	}
	if (!aux && !env)
		aux = ft_strdup(str);
	return (aux);
}

/**
 * * Given str expand env variables to their values for heredoc
 * @param maloc_str		malloc str to expand it content
 * @return				str expanded
*/
char	*ft_expand_heredoc(char *malloc_str)
{
	char	*tmp;
	char	*out;

	tmp = NULL;
	out = NULL;
	tmp = recursive_expand(malloc_str, IS_HEREDOC);
	out = ft_strreplace(tmp, "{0}", "$");
	free(tmp);
	return (out);
}
