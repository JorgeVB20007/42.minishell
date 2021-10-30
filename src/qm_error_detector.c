#include "minishell.h"

/*
* This function detects if there's quotation marks unclosed through the input 
* given. Quotation marks inside other types of quotation marks are excluded.
* If all goes well, the value 0 is returned.
*/
int	qm_error_detector(char *str)
{
	int		a;
	char	qm;

	a = 0;
	qm = 0;
	while (str[a])
	{
		if ((str[a] == '\'' || str[a] == '"') && (!a || str[a - 1] != '\\'))
		{
			if (!qm)
				qm = str[a];
			else if (qm == str[a])
				qm = 0;
		}
		a++;
	}
	if (qm)
	{
		write(1, "minishell: unclosed quotation marks\n", 55);
		return (1);
	}
	return (0);
}
