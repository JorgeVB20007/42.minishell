/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:36:26 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/07 20:49:02 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ? Function created for the project "minishell"
 * This function checks if a dollar sign ("$") can be considered as 
 * a valid variable format. It checks: 
 * - If the character before '$' (prv_char) is a '\'.
 * - If the character after '$' is alphanumeric or a '_'.
 * - If the '$' character is found between qoutaation marks.
*/
int	is_valid_var(char prv_char, char curr_char, char nxt_char, char qm)
{
	if (curr_char == '$' && prv_char != '\\' && \
	(ft_isalnum(nxt_char) || nxt_char == '_') && (qm == '"' || !qm))
		return (1);
	else
		return (0);
}
