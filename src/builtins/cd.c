#include "minishell.h"

#define HOME_NOT_SET "cd: HOME not set\n"
#define WRONG_CHDIR "cd: %s: No such file or directory\n"

/**
 * * Updates env's records of PWD and OLDPWD if exists
 * * OLDPWD get update with currrent env's PWD
 * * PWD get updated with current working directory
 * @param env_list	enviroment list
*/
static void update_env_pwd(t_str **env_list)
{
	t_str	*pwd;
	t_str	*old_pwd;
	char	*str;
	char	cwd[PATH_MAX - 1];

	old_pwd = ft_lst_str_get_str(env_list, LIT_OLDPWD_LIKE);
	if (old_pwd == NULL)
		old_pwd = ft_lst_str_get_str(env_list, LIT_OLDPWD);
	pwd = ft_lst_str_get_str(env_list, LIT_PWD_LIKE);
	if (old_pwd != NULL)
	{
		ft_lst_str_delete(env_list, old_pwd->str);
		if (pwd != NULL)
			str = ft_strjoin(LIT_OLDPWD, ft_strchr(pwd->str, '='));
		else
			str = ft_strdup(LIT_OLDPWD_LIKE);
		ft_lst_str_add_sorted(env_list, str);
	}
	if (pwd != NULL)
	{
		ft_lst_str_delete(env_list, pwd->str);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		str = ft_strjoin(LIT_PWD_LIKE, cwd);
		ft_lst_str_add_sorted(env_list, str);
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
		printf(WRONG_CHDIR, path);
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
		aux = ft_lst_str_get_str(env_list, LIT_HOME_LIKE);
		if (aux == NULL)
			printf(HOME_NOT_SET);
		else
			cant_chdir = ft_cant_chdir(ft_strchr(aux->str, '/'));
	}
	if (!cant_chdir)
		update_env_pwd(env_list);
}
