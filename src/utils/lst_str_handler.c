/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/07 10:07:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new str into list at alphabeticallly sorted
 * @param list	list
 * @param str	new str to link
*/
static void	ft_lst_str_add_sorted2(t_str **list, t_str	*new)
{
	t_str	*aux;

	aux = *list;
	if (ft_strncmp(new->str, aux->str, INT_MAX) < 0)
	{
		new->next = aux;
		*list = new;
	}
	while (aux != NULL)
	{
		if (ft_strncmp(new->str, aux->str, LONG_MAX) > 0 && (aux->next == NULL \
		|| ft_strncmp(new->str, aux->next->str, LONG_MAX) < 0))
		{
			new->next = aux->next;
			aux->next = new;
		}
		aux = aux->next;
	}
}

/**
 * * Add new str into list at alphabeticallly sorted
 * @param list	list
 * @param str	new str to link
*/
void	ft_lst_str_add_sorted(t_str **list, char *str)
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
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
		ft_lst_str_add_sorted2(list, new);
}

/**
 * * Free list
 * @param list	list
*/
void	ft_lst_str_free(t_str *list)
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
void	ft_lst_str_print(t_str *list)
{
	while (list != NULL)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}

/**
 * * Delete every str from list
 * @param list	list
 * @param str	str to delete
*/
void	ft_lst_str_delete(t_str **list, char *str)
{
	t_str	*prev;
	t_str	*aux;
	size_t	len;

	len = ft_strlen(str);
	ft_lst_str_add_front(list, NULL);
	prev = *list;
	aux = prev->next;
	while (aux != NULL)
	{
		if (!ft_strncmp(aux->str, str, len))
		{
			prev->next = aux->next;
			free(aux->str);
			free(aux);
		}
		else
			prev = prev->next;
		aux = prev->next;
	}
	aux = *list;
	*list = aux->next;
	free(aux);
}
