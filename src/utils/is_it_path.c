#include "minishell.h"

/*
?	Returns 1 if the given string has a path.
?	Returns 0 if the given string is something else, such a command.
!	This function does NOT check if the path exists. 
*	It just checks if the given string has a path format (contains '/'
*	or it's composed of a single '~').
*/
int	is_it_path(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] == '/')
			return (1);
		a++;
	}
	if (a == 1 && str[0] == '~')
		return (1);
	return (0);
}
