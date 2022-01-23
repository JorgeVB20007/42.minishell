/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/23 21:55:17 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define LIT_LAST_CMD "_="
#define LIT_SHLVL_LIKE "SHLVL="
#define LIT_SHLVL_LIKE_ONE "SHLVL=1"
#define LIT_EXEC_MINISHELL "./minishell"
#define ENV_NOT_OPTIONS_OR_ARGUMENT_ALLOWED "Minishell's subject \
'env with no options or arguments'\n"

/**
 * * Get a default env
 * @param signal	signal identifier (see man signal)
*/
static void	get_default_env(t_str **env_list)
{
	char	pwd[MAXPATHLEN];
	char	*pwd_command;

	pwd_command = NULL;
	getcwd(pwd, 100);
	lst_str_add_sorted(env_list, ft_strjoin(LIT_PWD_LIKE, pwd));
	lst_str_add_sorted(env_list, ft_strdup(LIT_SHLVL_LIKE_ONE));
	lst_str_add_sorted(env_list, ft_strdup(LIT_OLDPWD));
	pwd_command = ft_strjoin(pwd, LIT_EXEC_MINISHELL);
	lst_str_add_sorted(env_list, ft_strjoin(LIT_LAST_CMD, pwd_command));
	free(pwd_command);
}

/**
 * * Returns minishel enviroment SHLVL from current SHLVL
 * ? If not signed int +=1
 * ? If signed int =0
 * ? else =1
 * ? admits "     +000000000053" -> 54
 * ? admits "     -000000000053" -> 0
 * ? doesn't admit "     +-000000000053" -> 1
 * ? doesn't admit ISSPACE just spaces
 * @param shlvl		current shlvl
*/
static int	get_shlvl(char *shlvl)
{
	u_int32_t	nbr;
	u_int32_t	is_signed;

	if (shlvl == NULL)
		return (1);
	while (*shlvl == ' ')
		shlvl++;
	if (!ft_isdigit(*shlvl) && *shlvl != '-' && *shlvl != '+')
		return (1);
	nbr = 0;
	is_signed = (u_int32_t)(shlvl[0] == '-');
	shlvl += (*shlvl == '-' || *shlvl == '+');
	while (*shlvl != '\0' && nbr < INT_MAX)
	{
		if (ft_isdigit(*shlvl))
			nbr = nbr * 10 + *shlvl - '0';
		shlvl++;
	}
	if (nbr > INT_MAX + is_signed)
		return (1);
	else if (is_signed == 1)
		return (0);
	return (nbr + 1);
}

/**
 * * Initialize minishel enviroment variables list from input list
 * @param env_vector	input enviroment vector at exec ./minishell
 * @param env_list		output enviroment list returned
*/
void	init_ms_env(char **env_vector, t_str **env_list)
{
	int		i;
	char	*shlvl;

	if (env_vector[0] == NULL)
		get_default_env (env_list);
	else
	{
		i = 0;
		shlvl = NULL;
		while (env_vector[i] != NULL)
		{
			if (!ft_strncmp(env_vector[i], LIT_SHLVL_LIKE, 6))
				shlvl = ft_itoa(get_shlvl(ft_strchr(env_vector[i], '=') + 1));
			else
				lst_str_add_sorted(env_list, ft_strdup(env_vector[i]));
			i++;
		}
		if (!shlvl)
			lst_str_add_sorted(env_list, ft_strdup(LIT_SHLVL_LIKE_ONE));
		else
		{
			lst_str_add_sorted(env_list, ft_strjoin(LIT_SHLVL_LIKE, shlvl));
			free(shlvl);
		}
	}
}

/**
 * * This should recreate the bash funtion "env".
 * * Returms enviroment variables list
 * @param argv		vector of arguments (ERROR if not null)
*/
void	ft_env(char **argv)
{
	t_str	*aux;

	if (argv[1] != NULL && argv[1][0] != '|' && argv[1][0] != '<' \
	&& argv[1][0] != '>')
		log_error(ENV_NOT_OPTIONS_OR_ARGUMENT_ALLOWED, 1);
	else
	{
		aux = g_var.env;
		while (aux != NULL)
		{
			if (ft_strchr(aux->str, '='))
				printf("%s\n", aux->str);
			aux = aux->next;
		}
	}
}

/**
 * * This should recreate the stdlib.h funtion "getenv".
 * * Searches the environment list to find the environment variable name, \
 * * and returns a pointer to the corresponding value string
 * @param str		new str to look for
*/
char	*ft_getenv(const char *str)
{
	t_str	*aux;
	char	*str_like;

	str_like = ft_strjoin(str, "=");
	aux = lst_str_get_str(&g_var.env, str_like);
	free(str_like);
	if (aux == NULL)
		return ("");
	return (ft_strchr(aux->str, '=') + 1);
}
