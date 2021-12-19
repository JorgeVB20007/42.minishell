/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 08:19:36 by emadriga          #+#    #+#             */
/*   Updated: 2021/12/19 15:47:14 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define MS_PROMPT "Minishell> "
# define MS_PROMPT_SIG_INT "\033[KMinishell>   \n"
# define MSG_NEW_LINE "%s\n"
# define MSG_EXIT_MINISHELL "\033[AMinishell> exit\n"
# define LIT_OLDPWD "OLDPWD"
# define LIT_OLDPWD_LIKE "OLDPWD="
# define LIT_PWD_LIKE "PWD="
# define LIT_HOME_LIKE "HOME="
# define LIT_SHLVL_LIKE "SHLVL="
# define LIT_SHLVL_LIKE_ONE "SHLVL=1"
# define LIT_EXEC_MINISHELL "./minishell"
# define LIT_LAST_CMD "_="

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
