/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/09 12:58:44 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	ft_lst_str_add_sorted(env_list, ft_strjoin(LIT_PWD_LIKE, pwd));
	ft_lst_str_add_sorted(env_list, ft_strdup(LIT_SHLVL_LIKE_ONE));
	ft_lst_str_add_sorted(env_list, ft_strdup(LIT_OLDPWD));
	pwd_command = ft_strjoin(pwd, LIT_EXEC_MINISHELL);
	ft_lst_str_add_sorted(env_list, ft_strjoin(LIT_LAST_CMD, pwd_command));
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
				ft_lst_str_add_sorted(env_list, ft_strdup(env_vector[i]));
			i++;
		}
		if (!shlvl)
			ft_lst_str_add_sorted(env_list, ft_strdup(LIT_SHLVL_LIKE_ONE));
		else
		{
			ft_lst_str_add_sorted(env_list, ft_strjoin(LIT_SHLVL_LIKE, shlvl));
			free(shlvl);
		}
	}
}

/**
 * * This should recreate the bash funtion "env".
 * * Returms enviroment variables list
 * @param env_list	enviroment list
 * @param argv		vector of arguments (ERROR if not null)
*/
void	ft_env(t_str **env_list, char **argv)
{
	t_str	*aux;

	if (argv[1] != NULL)
		printf(ENV_NOT_OPTIONS_OR_ARGUMENT_ALLOWED);
	else
	{
		aux = *env_list;
		while (aux != NULL)
		{
			if (ft_strchr(aux->str, '='))
				printf("%s\n", aux->str);
			aux = aux->next;
		}
	}
}

/**
 * * Transform env linked list into vector as intended to work with execve
 * * Returms enviroment variables vector
 * @param env_list	enviroment list
*/
char	**env_list_to_vector(t_str **env_list)
{
	int		i;
	t_str	*aux;
	char	**envp;

	i = 0;
	aux = *env_list;
	while (aux != NULL)
	{
		aux = aux->next;
		i++;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	aux = *env_list;
	i = 0;
	while (aux != NULL)
	{
		envp[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
