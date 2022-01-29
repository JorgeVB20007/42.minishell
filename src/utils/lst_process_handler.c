/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_process_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:27:35 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/15 16:35:00 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new node into list at begining
 * @param list	list
 * @param new	new node to link
*/
void	lst_process_add_front(t_p **list, t_p *new)
{
	new->next = *list;
	*list = new;
}

/**
 * * Add new node into list at ending
 * @param list	list
 * @param new	new node to link
*/
void	lst_process_add_back(t_p **list, t_p *new)
{
	t_p	*aux;

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
t_p	*lst_process_new(void)
{
	t_p	*output;

	output = malloc(sizeof(t_p));
	if (!output)
		return (NULL);
	output->is_cmd = FALSE;
	output->is_builtin = FALSE;
	output->args = NULL;
	output->argv = NULL;
	output->pathname = NULL;
	output->redir = NULL;
	output->next = NULL;
	return (output);
}

/**
 * * Free list
 * @param list	list
*/
void	lst_process_free(t_p **list)
{
	t_p	*next;
	t_p	*aux;

	next = *list;
	aux = *list;
	while (next != NULL)
	{
		next = next->next;
		if (aux->pathname != NULL)
			free(aux->pathname);
		if (aux->argv != NULL)
			megafree(&aux->argv);
		if (aux->redir != NULL)
			lst_redir_free(&aux->redir);
		free(aux);
		aux = next;
	}
	*list = NULL;
	list = NULL;
}

/**
 * * Returns malloced node
*/
void	lst_process_print(t_p *list)
{
	int	i;

	dprintf(2, "\nPrinting processes\n");
	while (list != NULL)
	{
		i = 0;
		dprintf(2, "\nis_cmd %d\tis_builtin %d\tpathname %s\n argv ", \
		list->is_cmd, list->is_builtin, list->pathname);
		while (list->argv[i])
		{
			dprintf(2, "\t param[%d] %s\t", i, list->argv[i]);
			i++;
		}
		lst_redir_print(list->redir);
		list = list->next;
	}
}
