/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/07 11:54:50 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new str into list at front
 * @param list	list
 * @param str	new str to link
*/
void	ft_lst_str_add_front(t_str **list, char *str)
{
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		ft_lst_str_free(*list);
		free(str);
		exit(ENOMEM);
	}
	new->str = str;
	new->next = *list;
	*list = new;
}

/**
 * * Add new str into list at back
 * @param list	list
 * @param str	new str to link
*/
void	ft_lst_str_add_back(t_str **list, char *str)
{
	t_str	*new;
	t_str	*aux;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		ft_lst_str_free(*list);
		free(str);
		exit(ENOMEM);
	}
	new->str = str;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

/**
 * * Look for a str on the list returning if found
 * @param list	list
 * @param str	new str to look for
*/
t_str	*ft_lst_str_get_str(t_str **list, char *str)
{
	t_str	*aux;
	size_t	len;

	aux = *list;
	len = ft_strlen(str);
	while (aux != NULL)
	{
		if (!ft_strncmp(aux->str, str, len))
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}
