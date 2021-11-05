/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megafree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 22:23:47 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/05 22:27:30 by jvacaris         ###   ########.fr       */
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
