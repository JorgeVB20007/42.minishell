#include "libft.h"

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
