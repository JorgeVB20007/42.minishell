/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 08:19:36 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/05 21:49:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define LIT_OLDPWD "OLDPWD"
# define LIT_PWD_LIKE "PWD="
# define NONE 0

enum e_free_status
{
	NOT_FREE,
	FREE
};

enum e_quotes_status
{
	SINGLE = 1,
	DOUBLE
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_pipe_fd
{
	READ_END,
	WRITE_END
};

enum e_token
{
	APPENDS_OUTPUT_REDIRECT,
	BUILTIN,
	COMMAND,
	INPUT_REDIRECT,
	HEREDOC,
	OUPUT_REDIRECT,
	PIPE,
	TEXT
};
#endif
