/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:27:35 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/15 13:37:19 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new node into list at begining
 * @param list	list
 * @param new	new node to link
*/
void	lst_redir_add_front(t_redirection **list, t_redirection *new)
{
	new->next = *list;
	*list = new;
}

/**
 * * Add new node into list at ending
 * @param list	list
 * @param new	new node to link
*/
void	lst_redir_add_back(t_redirection **list, t_redirection *new)
{
	t_redirection	*aux;

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
t_redirection	*lst_redir_new(void)
{
	t_redirection	*output;

	output = malloc(sizeof(t_redirection));
	if (!output)
		return (NULL);
	output->type = NONE;
	output->go_to = NULL;
	output->next = NULL;
	return (output);
}

/**
 * * Free list
 * @param list	list
*/
void	lst_redir_free(t_redirection **list)
{
	t_redirection	*next;
	t_redirection	*aux;

	next = *list;
	aux = *list;
	while (next != NULL)
	{
		next = next->next;
		if (aux->go_to != NULL)
			free(aux->go_to);
		free(aux);
		aux = next;
	}
	*list = NULL;
	list = NULL;
}

/**
 * * Returns malloced node
*/
void	lst_redir_print(t_redirection *list)
{
	while (list != NULL)
	{
		printf("\nRedirection type %d\tgo to %s\n argv ", \
		list->type, list->go_to);
		list = list->next;
	}
}
