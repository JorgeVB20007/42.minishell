#include "libft.h"

/*
? Function created for the project "minishell"
* This function gets a string that could or could not start with '"' or '''.
* - If the function starts with any quotation mark, it will make a copy of 
*	that string without thw firstt and last quotation mark.
* - If the function does NOT start with a quotation mark, it will return 
*	a copy of the string given (this is done to make sure it's safe to free 
*	the return result after it's used).
! It only works when a string starts AND ENDS with a quotation mark.
*/
char	*qm_remover(char *qm_str)
{
	int		a;
	int		len;
	char	*ret;

	a = 0;
	ret = NULL;
	len = ft_strlen(qm_str);
	if (qm_str[a] != '\'' && qm_str[a] != '"')
		return (ft_strdup(qm_str));
	else
	{
		ret = ft_calloc(sizeof(char), len - 1);
		while (a < len - 2)
		{
			ret[a] = qm_str[a + 1];
			a++;
		}
	}
	return (ret);
}

static int	aqr_count(char *qm_str)
{
	int		a;
	int		count;
	char	qm;

	a = 0;
	count = 0;
	qm = 0;
	while (qm_str[a])
	{
		if (qm_str[a] == '\'' || qm_str[a] == '"')
		{
			if (!qm)
				qm = qm_str[a];
			else if (qm == qm_str[a])
			{
				qm = 0;
				count += 2;
			}
		}
		a++;
	}
	return (count);
}

static void	aqr_filler(char *qm_str, char **result)
{
	int		a;
	int		b;
	char	qm;

	a = 0;
	b = 0;
	qm = 0;
	while (qm_str[a])
	{
		if (qm_str[a] == '\'' || qm_str[a] == '"')
		{
			if (qm == qm_str[a])
				qm = 0;
			else if (qm)
				(*result)[b++] = qm_str[a];
			else if (!qm && ft_strchr(&qm_str[a + 1], qm) == NULL)
				(*result)[b++] = qm_str[a];
			else
				qm = qm_str[a];
		}
		else
			(*result)[b++] = qm_str[a];
		a++;
	}
}

char	*adv_qm_rem(char *qm_str)
{
	char	*result;
	int		less_chars;

	less_chars = aqr_count(qm_str);
	result = NULL;
	if (!less_chars)
		return (ft_strdup(qm_str));
	result = ft_calloc((sizeof(char)), ft_strlen(qm_str) - less_chars + 1);
	aqr_filler(qm_str, &result);
	return (result);
}
