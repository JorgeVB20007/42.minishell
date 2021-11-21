/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_red_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:27:35 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/21 19:03:47 by jvacaris         ###   ########.fr       */
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
	dprintf(2, "> %p <\n", output);
	return (output);
}

/**
 * * Free list
 * @param list	list
*/
void	lst_red_free(t_red **list)
{
	t_red	*next;
	t_red	*aux;

	next = *list;
	aux = *list;
	while (next != NULL)
	{
		next = next->next;
		free(aux->path);
		megafree(&aux->params);
		megafree(&aux->redirs);
		free(aux);
		aux = next;
	}
	*list = NULL;
}

/**
 * * Returns malloced node
*/
void	lst_red_print(t_red *list)
{
	int	i;

	dprintf(2, "\nPrinting\n");
	while (list != NULL)
	{
		i = 0;
		dprintf(2, "\npid_in %d\tpip_out %d\tpath %s\n Params ", \
		list->pip_in, list->pip_out, list->path);
		while (list->params[i])
		{
			dprintf(2, "\t param[%d] %s\t", i, list->params[i]);
			i++;
		}
		i = 0;
		dprintf(2, "\n redirs");
		while (list->redirs[i])
		{
			dprintf(2, "\t redirs[%d] %s\t", i, list->redirs[i]);
			i++;
		}
		list = list->next;
	}
}
