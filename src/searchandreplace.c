#include "minishell.h"

char *getvarvalue(char *str)
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

void	expand_var(char *orgn, char **end, int *a, int *b)
{
	char	*value;
	int		c;

	(*a)++;
	c = 0;
	value = getvarvalue(&orgn[*a]);
	while (value[c])
		(*end)[(*b)++] = value[c++];
	while ((ft_isalnum(orgn[*a]) || orgn[*a] == '_') && orgn[*a])
		(*a)++;
}

void dollarfound_getlen(int *a, int *count, char *input)
{
	(*a)++;
	if (getvarvalue(&input[*a]))
		*count += ft_strlen(getvarvalue(&input[*a]));
	while ((ft_isalnum(input[*a]) || input[*a] == '_') && input[*a])
		(*a)++;
}