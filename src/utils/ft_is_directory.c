#include "minishell.h"

/*
*	This function checks whether a given path corresponds to a file or
*	a directory. Return values:
?	1 if the path corresponds to a file.
?	0 if the path corresponds to a directory.
*/
int	ft_is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}
