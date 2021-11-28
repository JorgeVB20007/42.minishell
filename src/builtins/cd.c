#include "minishell.h"

#define HOME_NOT_SET "cd: HOME not set\n"
#define WRONG_CHDIR "cd: %s: No such file or directory\n"

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
	char	cwd[PATH_MAX - 1];

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
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
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

	cant_chdir = chdir(path);
	if (cant_chdir != 0)
		log_error_free(ft_strreplace(WRONG_CHDIR, "{0}", path), 1);
	return (cant_chdir);
}

/**
 * * This should recreate the bash funtion "cd".
 * * Shall change the working directory of the current shell execution
 * @param env_list	enviroment list
 * @param argv	vector of arguments containing records to add
*/
void	ft_cd(t_str **env_list, char **argv)
{
	t_str	*aux;
	int		cant_chdir;

	cant_chdir = 1;
	if (argv[1] != NULL)
		cant_chdir = ft_cant_chdir(argv[1]);
	else
	{
		aux = lst_str_get_str(env_list, LIT_HOME_LIKE);
		if (aux == NULL)
			log_error(HOME_NOT_SET, 1);
		else
			cant_chdir = ft_cant_chdir(ft_strchr(aux->str, '/'));
	}
	if (!cant_chdir)
		update_env_pwd(env_list, lst_str_get_str(env_list, LIT_PWD_LIKE), \
						lst_str_get_str(env_list, LIT_OLDPWD_LIKE));
}
