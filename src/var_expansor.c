/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:09:24 by jvacaris          #+#    #+#             */
/*   Updated: 2021/10/27 19:25:20 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function recieves the adress of the first character of a 
 * variable's name ($varname), reads the variaable name, gets 
 * it's value and returns it.
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
	(*a)++;
	if (getvarvalue(&input[*a]))
		*count += ft_strlen(getvarvalue(&input[*a]));
	while ((ft_isalnum(input[*a]) || input[*a] == '_') && input[*a])
		(*a)++;
}
