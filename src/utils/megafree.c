/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megafree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 22:23:47 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/09 12:16:03 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* This function recieves a list of strings (pointer to pointers) and frees
* everything, including the main pointer. The last string must be NULL.
*/
void	megafree(char ***list)
{
	int	a;

	a = 0;
	while ((*list)[a])
		free((*list)[a++]);
	free((*list)[a]);
	free(*list);
}

/**
 * * Print array of strings
 * @param array	array
*/
void	ft_array_str_print(char **array)
{
	int	a;

	a = 0;
	while (array[a])
		printf("%s\n", array[a++]);
}
