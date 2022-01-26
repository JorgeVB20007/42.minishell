/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:50:27 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/26 15:43:29 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define LIT_HOME_LIKE "HOME="
#define HOME_NOT_SET "cd: HOME not set\n"

/**
 * * Updates env's records of PWD and OLDPWD if exists
 * * OLDPWD get update with currrent env's PWD
 * * PWD get updated with current working directory
 * @param env_list	enviroment list
 * @param pwd		env's current PWD
 * @param old_pwd	env's current OLDPWD
*/
static void	update_env_pwd(t_str **env_list, t_str	*pwd, t_str	*old_pwd)
{
	char	*str;
	char	cwd[PATH_MAX];

	if (old_pwd == NULL)
		old_pwd = lst_str_get_str(env_list, LIT_OLDPWD);
	if (old_pwd != NULL)
	{
		lst_str_delete(env_list, old_pwd->str, ULONG_MAX);
		if (pwd != NULL)
			str = ft_strjoin(LIT_OLDPWD, ft_strchr(pwd->str, '='));
		else
			str = ft_strdup(LIT_OLDPWD_LIKE);
		lst_str_add_sorted(env_list, str);
	}
	if (pwd != NULL)
	{
		lst_str_delete(env_list, pwd->str, ULONG_MAX);
		getcwd(cwd, PATH_MAX);
		str = ft_strjoin(LIT_PWD_LIKE, cwd);
		lst_str_add_sorted(env_list, str);
	}
}

/**
 * * Changes the current working directory of the calling process to the
 * * directory specified in path. On success, zero is returned. On error,
 * * -1 is returned, and errno is set to indicate the error.
 * @param path	path
*/
static int	ft_cant_chdir(const char *path)
{
	int		cant_chdir;
	char	*composed_error;

	composed_error = NULL;
	cant_chdir = chdir(path);
	if (cant_chdir != 0)
	{
		composed_error = ft_strjoin("Minishell: cd: ", path);
		perror(composed_error);
		free(composed_error);
		g_var.current_status = 1;
	}
	return (cant_chdir);
}

/**
 * * This should recreate the bash funtion "cd".
 * * Shall change the working directory of the current shell execution
 * @param argv	vector of arguments containing records to add
*/
void	ft_cd(char **argv)
{
	t_str	**env_list;
	t_str	*aux;
	int		cant_chdir;

	cant_chdir = 1;
	env_list = &g_var.env;
	if (argv[1] != NULL)
		cant_chdir = ft_cant_chdir(argv[1]);
	else
	{
		aux = lst_str_get_str(&g_var.env, LIT_HOME_LIKE);
		if (aux == NULL)
			log_error(HOME_NOT_SET, 1);
		else
			cant_chdir = ft_cant_chdir(ft_strchr(aux->str, '/'));
	}
	if (!cant_chdir)
		update_env_pwd(env_list, lst_str_get_str(env_list, LIT_PWD_LIKE), \
						lst_str_get_str(env_list, LIT_OLDPWD_LIKE));
}
