/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslashjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 22:24:28 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/05 22:24:33 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strslashjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	join = ft_calloc(sizeof(char), len);
	if (!join)
		return (0);
	ft_strlcat(join, s1, len);
	ft_strlcat(join, "/", len);
	ft_strlcat(join, s2, len);
	return (join);
}
