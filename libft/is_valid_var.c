#include "libft.h"

/*
 * This function checks if a dollar sign ("$") can be considered as 
 * a valid variable format. It checks: 
 * - If the character before '$' (prv_char) is a '\'.
 * - If the character after '$' is alphanumeric or a '_'.
 * - If the '$' character is found between qoutaation marks.
*/
int	is_valid_var(char prv_char, char curr_char, char nxt_char, char qm)
{
	if (curr_char == '$' && prv_char != '\\' && \
	(ft_isalnum(nxt_char) || nxt_char == '_') && (qm == '"' || !qm))
		return (1);
	else
		return (0);
}
