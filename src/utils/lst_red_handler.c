/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_red_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:27:35 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/20 11:27:36 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new node into list at begining
 * @param list	list
 * @param new	new node to link
*/
void	lst_red_add_front(t_red **list, t_red *new)
{
	new->next = *list;
	*list = new;
}

/**
 * * Add new node into list at ending
 * @param list	list
 * @param new	new node to link
*/
void	lst_red_add_back(t_red **list, t_red *new)
{
	t_red	*aux;

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
 * * Returns malloced node
*/
t_red	*lst_red_new(void)
{
	t_red	*output;

	output = malloc(sizeof(t_red));
	if (!output)
		return (NULL);
	output->next = NULL;
	return (output);
}

/**
 * * Free list
 * @param list	list
*/
void	lst_red_free(t_red *list)
{
	t_red	*next;
	t_red	*aux;

	next = list;
	aux = list;
	while (next != NULL)
	{
		next = next->next;
		// free every node element needed
		free(aux->path); // ? if our ft_getenv is ft_duped, otherwise we re freeing our ENV's PATH
		megafree(&aux->params);
		megafree(&aux->redirs);
		free(aux); // free node
		aux = next;
	}
}
