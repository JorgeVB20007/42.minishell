/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 08:19:36 by emadriga          #+#    #+#             */
/*   Updated: 2021/12/24 16:20:22 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define LIT_OLDPWD "OLDPWD"
# define LIT_PWD_LIKE "PWD="

enum e_free_status
{
	NOT_FREE,
	FREE
};

enum e_quotes_status
{
	NONE,
	SINGLE,
	DOUBLE
};

enum e_bool
{
	FALSE,
	TRUE
};

#endif
