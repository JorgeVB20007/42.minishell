/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:09:24 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/27 17:34:38 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Get next index of a str to expand
 * @param str		str to expand it content
 * @return			str expanded
*/
static size_t	get_start_expand(const char *str)
{
	int		quotes;
	char	*start_expand;

	quotes = NONE;
	start_expand = (char *)str;
	while (*start_expand != '\0')
	{
		if (quotes == NONE && *start_expand == '$')
			return (start_expand - str);
		else if (quotes == NONE && *start_expand == '\'')
			quotes = SINGLE;
		else if (quotes == SINGLE && *start_expand == '\'')
			quotes = NONE;
		start_expand++;
	}
	return (0);
}

/**
 * * Replace environment variable of given str from start with some lenght
 * * Frees input str malloc
 * @param malloc_str	str to expand it content
 * @param env_list		environment list
 * @param start_expand	index of start to replace
 * @param len_expand	lenght to replace
 * @return				str expanded
*/
static char	*expand_at_free(char *malloc_str, t_str **env_list, \
				size_t start_expand, size_t len_expand)
{
	char	*oldset;
	char	*newset;
	char	*out;

	oldset = ft_substr(malloc_str, start_expand, len_expand);
	newset = ft_getenv(env_list, &oldset[1]);
	if (!newset)
		out = ft_strreplaceat(malloc_str, oldset, "", start_expand);
	else
		out = ft_strreplaceat(malloc_str, oldset, newset, start_expand);
	free(malloc_str);
	free(oldset);
	return (out);
}

/**
 * * Given str expand environment variables ($ followed by characters) to their values
 * * Input str should come malloc
 * @param malloc_str	str to expand it content
 * @param env_list		environment list
 * @return				str expanded
*/
char	*recursive_expand(char *malloc_str, t_str **env_list)
{
	size_t	start_expand;
	size_t	len_expand;
	char	*aux;

	start_expand = get_start_expand(malloc_str);
	if (start_expand != 0)
	{
		len_expand = 1;
		aux = &malloc_str[start_expand];
		while (ft_isalnum(aux[len_expand]) || aux[len_expand] == '_')
			len_expand++;
		malloc_str = expand_at_free(malloc_str, env_list, \
							start_expand, len_expand);
		return (recursive_expand(malloc_str, env_list));
	}
	return (malloc_str);
}
