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
void	ft_lst_str_add_front(t_str **list, char *str)
{
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
	{
		ft_lst_str_free(list);
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
		ft_lst_str_free(list);
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
t_str	*ft_lst_str_get_str(t_str **list, const char *str)
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
 * * This should recreate the stdlib.h funtion "getenv".
 * * Searches the environment list to find the environment variable name, \
 * * and returns a pointer to the corresponding value string
 * @param env_list	enviroment list
 * @param str		new str to look for
*/
char	*ft_getenv(t_str **env_list, const char *str)
{
	t_str	*aux;
	char	*str_like;

	str_like = ft_strjoin(str, "=");
	aux = ft_lst_str_get_str(env_list, str_like);
	free(str_like);
	if (aux == NULL)
		return ("");
	return (ft_strchr(aux->str, '=') + 1);
}
