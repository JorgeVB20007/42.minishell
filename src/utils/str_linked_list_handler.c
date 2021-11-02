/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_linked_list_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/01 18:10:39 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new str into list at back
 * @param list	list
 * @param str	new str to link
*/
void	ft_lstadd_back_str(t_str **list, char *str)
{
	t_str	*new;
	t_str	*aux;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		ft_freelst_str(*list);
		free(str);
		exit(ENOMEM);
	}
	new->str = str;
	new->next = NULL;
	new->prev = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		new->prev = aux;
		aux->next = new;
	}
}

/**
 * * Free list
 * @param list	list
*/
void	ft_freelst_str(t_str *list)
{
	t_str	*next;
	t_str	*aux;

	next = list;
	aux = list;
	while (next != NULL)
	{
		next = next->next;
		free(aux->str);
		free(aux);
		aux = next;
	}
}

/**
 * * Print list
 * @param list	list
*/
void	ft_printlist_str(t_str *list)
{
	while (list != NULL)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}

/**
 * * Delete str from list
 * @param list	list
 * @param str	str to delete
*/
void	ft_lstdelete_str(t_str **list, char *str)
{
	t_str	*prev;
	t_str	*aux;
	size_t	len;

	len = ft_strlen(str);
	while (ft_strcmp(*list->str, str, len))
	{
		aux = *list;
		*list = *list->next;
		free(aux->str);
		free(aux);
	}
	prev = *listt;
	while (aux != NULL)
	{
		aux = prev->next;
		if (ft_strcmp(aux->str, str, len))
		{
			prev->next = aux->next;
			free(aux->str);
			free(aux);
		}
		else
			prev = prev->next;
	}
}

