/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:09:24 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/23 23:38:23 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXPAND_STATUS "$?"

/**
 * * Get next index of a str to expand
 * @param str			str to expand it content
 * @param is_heredoc	is called from heredoc
 * @return				str expanded
*/
static size_t	get_start_expand(const char *str, int is_heredoc)
{
	int		quotes;
	char	*start_expand;

	quotes = NONE;
	start_expand = (char *)str;
	while (*start_expand != '\0')
	{
		if (quotes == NONE && *start_expand == '$')
			return (start_expand - str);
		else if (!is_heredoc && quotes == NONE && *start_expand == '\'')
			quotes = SINGLE;
		else if (!is_heredoc && quotes == SINGLE && *start_expand == '\'')
			quotes = NONE;
		start_expand++;
	}
	return (0);
}

/**
 * * Replace exit status of the last executed command on given str from start
 * @param str			str to expand it content
 * @param start_expand	index of start to replace
 * @return				str expanded
*/
static char	*expand_status_at(char *str, size_t start_expand)
{
	char	*newset;
	char	*out;

	newset = ft_itoa(g_var.last_cmd_status);
	out = ft_strreplaceat(str, EXPAND_STATUS, newset, start_expand);
	free(newset);
	return (out);
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
static char	*expand_at_free(char *malloc_str,  \
				size_t start_expand, size_t len_expand)
{
	char	*oldset;
	char	*newset;
	char	*out;

	oldset = ft_substr(malloc_str, start_expand, len_expand);
	if (!ft_strncmp(oldset, EXPAND_STATUS, 2))
		out = expand_status_at(malloc_str, start_expand);
	else
	{
		newset = ft_getenv(&oldset[1]);
		if (!newset)
			out = ft_strreplaceat(malloc_str, oldset, "", start_expand);
		else
			out = ft_strreplaceat(malloc_str, oldset, newset, start_expand);
	}
	free(malloc_str);
	free(oldset);
	return (out);
}

/**
 * * Given str expand env variables ($ followed by characters) to their values
 * * Input str should come malloc
 * @param malloc_str	str to expand it content
 * @param is_heredoc	is called from heredoc
 * @return				str expanded
*/
char	*recursive_expand(char *malloc_str, int is_heredoc)
{
	size_t	start_expand;
	size_t	len_expand;
	char	*aux;

	start_expand = get_start_expand(malloc_str, is_heredoc);
	if (start_expand != 0 || malloc_str[0] == '$')
	{
		len_expand = 1;
		aux = &malloc_str[start_expand];
		while (ft_isalnum(aux[len_expand]) || aux[len_expand] == '_')
			len_expand++;
		if (len_expand == 1 && aux[len_expand] == '?')
			len_expand = 2;
		malloc_str = expand_at_free(malloc_str, \
								start_expand, len_expand);
		return (recursive_expand(malloc_str, is_heredoc));
	}
	return (malloc_str);
}

/**
 * * Given str expand env variables ($ followed by characters) to their values
 * @param str			str to expand it content
 * @return				str expanded
*/
char	*ft_expand(const char *str)
{
	return (recursive_expand(ft_strdup(str), FALSE));
}
