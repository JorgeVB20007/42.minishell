#include "minishell.h"

/*
 * This function recieves an origin string (orgn), a pointer to the end string 
 * (end) and the length (len) of the desired end string (excluding the final 0).
 * If a '\' followed by ' ' is found, the '\' will be skipped and not copied into end.
 * The variable qm is set to 0. If it encounters any quotation mark (''', '"'), 
 * it will be set to that character until the character is found somewhere again.
*/
static int	ft_modstrcpy(char *orgn, char **end, int len)
{
	int		a;
	int		b;
	char	qm;

	a = 0;
	b = 0;
	qm = 0;
	while (b < len)
	{
		if ((orgn[a] == '\'' || orgn[a] == '"') && !qm)
			qm = orgn[a];
		else if (qm == orgn[a] && qm)
			qm = 0;
		if (orgn[a] == '\\' && orgn[a + 1] == ' ' && !qm)
			a++;
		(*end)[b] = orgn[a];
		a++;
		b++;
	}
	(*end)[b] = 0;
	return(a);
}

/*
 * If a quotation mark is found while checking the length of a parameter, this 
 * function keeps counting until a quotation mark of the same type is found (as long 
 * as it's not preceeded by '\'), ignoring spaces and other types of quotation marks.
*/
static void	quotemarksfound(int *a, int *count, char *input, char quotemark)
{
	(*a)++;
	(*count)++;
	while ((input[*a] != quotemark || input[*a - 1] == '\\') && input[*a])
	{
		(*count)++;
		(*a)++;
	}
}

/*
 * Checking the length of the string given, starting from index a and ending 
 * as soon as a space ' ' character is found (as long as it's not preceeded 
 * by '\' or contained inside single or double quotation marks).
*/
static int	checklen(char *input, int a)
{
	int	count;

	count = 0;
	while (input[a] != 0 && (input[a] != ' ' || input[a - 1] == '\\'))
	{
		if ((input[a] == '"' || input[a] == '\'') && (a == 0 || input[a - 1] != '\\'))
			quotemarksfound(&a, &count, input, input[a]);
		if (input[a] == '\\' && input[a + 1] == ' ')
			count--;
		count++;
		a++;
	}
	return(count);
}

/*
 * Reserving memory to fit all the parameters, then counting how many 
 * characters are inside each parameter, reserving memory for each of 
 * them and then copying each parameter into each reserved space.
*/
static char	**fillparams(char *input, int params)
{
	char	**result;
	int		a;
	int		count;
	int		len;

	count = 0;
	a = 0;
	result = malloc(sizeof(char *) * (params + 1));
	result[params] = NULL;
	while (input[a] && input[a] == ' ')
		a++;
	while (input[a] != 0)
	{
		len = checklen(input, a);
		result[count] = malloc(len + 1);
		a = a + ft_modstrcpy(&input[a], &result[count], len);
		//ft_strlcpy(result[count], &input[a], len + 1);
		while (input[a] && input[a] == ' ')
			a++;
		count++;
	}
	return (result);
}

/*
 * * Counting how many parameters are found in the string given. Params 
 * * are separated by a space ' ', as long as it's not preceeded by a '\' 
 * * or it's not inside single ''' or double '"' quotation marks.
*/
static int	countparams(char *input)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (input[a] && input[a] == ' ')
		a++;
	if (input[a])
		count++;
	while (input[a] != 0)
	{
		if (input[a] == ' ' && input[a - 1] != '\\')
		{
			count++;
			while (input[a] == ' ' && input[a])
				a++;
		}
		if (input[a] == '"' && (a == 0 || input[a - 1] != '\\'))
		{
			a++;
			while ((input[a] != '"' || input[a - 1] == '\\') && input[a])
				a++;
		}
		else if (input[a] == '\'' && (a == 0 || input[a - 1] != '\\'))
		{
			a++;
			while ((input[a] != '\'' || input[a - 1] == '\\') && input[a])
				a++;
		}
		a++;
	}
	if (input[a - 1] == ' ')
		count--;
	return (count);
}

/**
 * ? test ./minishell "cat -e hello"
 * * Parse every input to the minishell, returning a string list with processed 
 * * information 
 * @param input		input
*/
char	**modifsplit(char *input)
{
	int		params;
	char	**result;

	params = countparams(input);
	result = fillparams(input, params);
	return (result);
}

/*
 * For testing purposes only. Remove or comment while testing other programs.
 ? ./minishell "cat -e hello"
*/
int	main(int argc, char **argv)
{
	argc = 0;
	char	**result;

	printf("\n\033[0;32mInput:\033[0;33m %s\n\n\033[0;32mResult:\n\033[0;37m", argv[1]);
	result = modifsplit(argv[1]);
	while(result[argc])
	{
		printf("\033[0;36m%d - \033[0;37m%s\n", argc, result[argc]);
		argc++;
	}
	printf("%s\n\n", result[argc]);


	printf("\n\n\n\n%s\n", getenv("lsdghld"));
}
