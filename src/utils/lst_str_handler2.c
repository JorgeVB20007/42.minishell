/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/21 19:11:04 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Add new str into list at front
 * @param list	list
 * @param str	new str to link
*/
void	lst_str_add_front(t_str **list, char *str)
{
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		lst_str_free(list);
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
void	lst_str_add_back(t_str **list, char *str)
{
	t_str	*new;
	t_str	*aux;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		lst_str_free(list);
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
 * * Look for a str on the list returning node if found
 * @param list	list
 * @param str	new str to look for
*/
t_str	*lst_str_get_str(t_str **list, const char *str)
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

/**
 * * Transform str linked list into array
 * * Returns array of str
 * @param list	str list
*/
char	**lst_str_to_array(t_str **list)
{
	int		i;
	t_str	*aux;
	char	**array;

	i = 0;
	aux = *list;
	while (aux != NULL)
	{
		aux = aux->next;
		i++;
	}
	array = malloc(sizeof(char *) * (i + 1));
	aux = *list;
	i = 0;
	while (aux != NULL)
	{
		array[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	array[i] = NULL;
	return (array);
}
