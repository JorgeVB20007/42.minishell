/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:09:24 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/20 13:38:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function recieves the adress of the first character of a
 * variable's name ($varname), reads the variable name, gets
 * it's value and returns it.
 * Inputting the trimmed variable name is not required.
*/
char	*getvarvalue(char *str)
{
	int		a;
	char	*varname;
	char	*result;

	a = 0;
	while ((ft_isalnum(str[a]) || str[a] == '_') && str[a])
		a++;
	varname = ft_calloc(sizeof(char), a + 1);
	a = 0;
	while ((ft_isalnum(str[a]) || str[a] == '_') && str[a])
	{
		varname[a] = str[a];
		a++;
	}
	result = getenv(varname);
	free(varname);
	return (result);
}

/*
 *This function recieves a string (orgn) and it's current position (a),
 * and a pointer to a string (end) and it's current position.
 *The function is called once the parent function locates a variable name.
 * This will read the variable name, get it's value, copy it into end and
 * advance both indexes (a and b) to the last character read/written so
 * the parent function can keep working.
*/
void	expand_var(char *orgn, char **end, int *a, int *b)
{
	char	*value;
	int		c;

	(*a)++;
	c = 0;
	value = getvarvalue(&orgn[*a]);
	if (value)
	{
		while (value[c])
			(*end)[(*b)++] = value[c++];
	}
	while ((ft_isalnum(orgn[*a]) || orgn[*a] == '_') && orgn[*a])
		(*a)++;
}

/*
 * This function is similar to expand_var, but it will not copy the result
 * of the variable into any string. It just counts the length of the
 * variable and advances the index to the string to the end of the var name.
*/
void	dollarfound_getlen(int *a, int *count, char *input)
{
	char	*value;

	value = NULL;
	value = getvarvalue(&input[*a]);
	(*a)++;
	if (value)
		*count += ft_strlen(value);
	while ((ft_isalnum(input[*a]) || input[*a] == '_') && input[*a])
		(*a)++;
}

/**
 * * Get next index of a str to expand
 * @param str		str to expand it content
 * @return			str expanded
*/
static size_t get_start_expand(const char *str)
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
static char *expand_at_free(char *malloc_str, t_str **env_list, size_t start_expand, \
							 size_t len_expand)
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
		malloc_str = expand_at_free(malloc_str, env_list, start_expand, len_expand);
		return (recursive_expand(malloc_str, env_list));
	}
	return (malloc_str);
}
