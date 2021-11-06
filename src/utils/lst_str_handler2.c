/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_handler copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/06 20:19:58 by emadriga         ###   ########.fr       */
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
