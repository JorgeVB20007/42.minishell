/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:18:24 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/29 18:05:53 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define LITERAL_PATH "PATH"
#define COMMAND_NOT_FOUND "Error: command {0} not found.\n"
#define PATH_NOT_FOUND "Error: env variable 'PATH' not found.\n"
#define IS_DIRECTORY "{0}: is a directory\n"
#define PERM_DENIED "{0}: Permission denied\n"
#define FILE_NOT_FOUND "{0}: No such file or directory\n"

/*
?   (Continuación de la función de abajo)
*/
static char	*new_get_command_path(char *command)
{
	int		idx;
	char	*str_att;
	char	*paths;
	char	**path_list;

	idx = 0;
	paths = ft_getenv(LITERAL_PATH);
	if (!paths[0])
	{
		log_error(PATH_NOT_FOUND, 1);
		return (NULL);
	}
	path_list = ft_split(paths, ':');
	while (path_list[idx])
	{
		str_att = ft_strslashjoin(path_list[idx++], command);
		if (!access(str_att, X_OK))
			break ;
		free(str_att);
		str_att = NULL;
	}
	megafree(&path_list);
	if (str_att == NULL)
		log_error_free(ft_strreplace(COMMAND_NOT_FOUND, "{0}", command), 127);
	return (str_att);
}

/*
?   Esta función te saca el path correcto para el comando que le pasas.
?   Si le pasas la dirección a un ejecutable, te devuelve esa misma
?   dirección malloqueada.
*/
char	*new_getpath(char *raw_cmd)
{
	if (is_it_path(raw_cmd))
	{
		if (access(raw_cmd, F_OK))
		{
			log_error_free(ft_strreplace(FILE_NOT_FOUND, "{0}", raw_cmd), 127);
			g_var.current_status = 127;
		}
		else if (!ft_is_directory(raw_cmd))
		{
			log_error_free(ft_strreplace(IS_DIRECTORY, "{0}", raw_cmd), 126);
			g_var.current_status = 126;
		}
		else if (access(raw_cmd, X_OK))
		{
			log_error_free(ft_strreplace(PERM_DENIED, "{0}", raw_cmd), 126);
			g_var.current_status = 126;
		}
		else
			return (ft_strdup(raw_cmd));
		return (NULL);
	}
	return (new_get_command_path(raw_cmd));
}
