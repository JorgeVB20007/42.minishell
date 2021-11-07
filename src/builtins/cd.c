#include "minishell.h"

#define HOME_NOT_SET "cd: HOME not set\n"
#define WRONG_CHDIR "cd: %s: No such file or directory\n"

void static	update_env_pwd(t_str **env_list)
{
	t_str	*pwd;
	t_str	*old_pwd;
	char	*str;
	char	cwd[PATH_MAX - 1];

	old_pwd = ft_lst_str_get_str(env_list, "OLDPWD=");
	pwd = ft_lst_str_get_str(env_list, "PWD=");
	if (old_pwd != NULL)
	{
		ft_lst_str_delete(env_list, old_pwd->str);
		if (pwd != NULL)
			str = ft_strjoin("OLDPWD", ft_strchr(pwd->str, '='));
		else
			str = ft_strdup("OLDPWD=");
		ft_lst_str_add_sorted(env_list, str);
	}
	if (pwd != NULL)
	{
		ft_lst_str_delete(env_list, pwd->str);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		str = ft_strjoin("PWD=", cwd);
		ft_lst_str_add_sorted(env_list, str);
	}
}

int static	ft_cant_chdir(const char *str)
{
	int		cant_chdir;

	cant_chdir = chdir(str);
	if (cant_chdir != 0)
		printf(WRONG_CHDIR, str);
	return (cant_chdir);
}


/**
 * * This should recreate the bash funtion "cd".
 * * Shall change the working directory of the current shell execution
 * 
 * CHDIR handles . and ..
 * if empty look HOME on end and try to go there
 * 
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
		aux = ft_lst_str_get_str(env_list, "HOME=");
		if (aux == NULL)
			printf(HOME_NOT_SET);
		else
			cant_chdir = ft_cant_chdir(aux->str);
	}
	if (!cant_chdir)
		update_env_pwd(env_list);
}
