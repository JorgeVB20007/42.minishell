/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 08:19:36 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/31 09:05:15 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define LIT_OLDPWD "OLDPWD"
# define LIT_PWD_LIKE "PWD="
# define LIT_OLDPWD_LIKE "OLDPWD="
# define NONE 0

enum e_free_status
{
	NOT_FREE,
	FREE
};

enum e_expanse_heredoc
{
	NOT_HEREDOC,
	IS_HEREDOC
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

enum e_elephants_fd
{
	PLAYING,
	PUNISHED
};

enum e_token
{
	APPENDS_OUTPUT_REDIRECT = 1,
	BUILTIN,
	COMMAND,
	INPUT_REDIRECT,
	HEREDOC,
	OUPUT_REDIRECT,
	PIPE,
	TEXT
};
#endif
