#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_strcpy(char *orgn, char **end, int len)
{
	int	a;

	a = 0;
	while (a < len)
	{
		(*end)[a] = orgn[a];
		a++;
	}
	(*end)[a] = 0;
}

int	checklen(char *input, int a)
{
	int count;

	count = 0;
	while (input[a] != 0 && (input[a] != ' ' || input[a - 1] == '\\'))
	{
		if (input[a] == '"' && (a == 0 || input[a - 1] != '\\'))
		{
			a++;
			count++;
			while ((input[a] != '"' || input[a - 1] == '\\') && input[a])
			{
				count++;
				a++;
			}
		}
		else if (input[a] == '\'' && (a == 0 || input[a - 1] != '\\'))
		{
			a++;
			count++;
			while ((input[a] != '\'' || input[a - 1] == '\\') && input[a])
			{
				count++;
				a++;
			}
		}
		count++;
		a++;
	}
	return (count);
}

char	**fillparams(char *input, int params)
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
		ft_strcpy(&input[a], &result[count], len);
		a = a + len;
		while (input[a] && input[a] == ' ')
			a++;
		count++;
	}
	return (result);
}

int countparams(char *input)
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

char **modifsplit(char *input)
{
	int		params;
	char	**result;

	params = countparams(input);
	result = fillparams(input, params);
	return (result);
}

int main(int argc, char **argv)
{
	argc = 0;
	char	**result;

	printf("\033[0;32mInput:\033[0;33m %s\n\n\033[0;32mResult:\n\033[0;37m", argv[1]);

	result = modifsplit(argv[1]);
	while(result[argc])
		printf("%s\n", result[argc++]);
	printf("%s\n", result[argc]);
}