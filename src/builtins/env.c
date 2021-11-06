/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 19:28:26 by emadriga          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/05 19:50:09 by jvacaris         ###   ########.fr       */
=======
/*   Updated: 2021/11/06 20:51:26 by emadriga         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_lst_str_add_sorted(env_list, ft_strjoin("PWD=", pwd));
	ft_lst_str_add_sorted(env_list, ft_strdup("SHLVL=1"));
	pwd_command = ft_strjoin(pwd, "./minishell");
	ft_lst_str_add_sorted(env_list, ft_strjoin("_=", pwd_command));
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
			if (!ft_strncmp(env_vector[i], "SHLVL=", 6))
				shlvl = ft_itoa(get_shlvl(ft_strchr(env_vector[i], '=') + 1));
			else
				ft_lst_str_add_sorted(env_list, ft_strdup(env_vector[i]));
			i++;
		}
		if (!shlvl)
			ft_lst_str_add_sorted(env_list, ft_strdup("SHLVL=1"));
		else
		{
			ft_lst_str_add_sorted(env_list, ft_strjoin("SHLVL=", shlvl));
			free(shlvl);
		}
	}
}

/**
 * * This should recreate the bash funtion "env".
 * * Returms enviroment variables list
 * @param env_list	enviroment list
*/
void	ft_env(t_str *env_list)
{
	ft_lst_str_print(env_list);
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
<<<<<<< HEAD
	while (aux == NULL && i++)
=======
	while (aux != NULL)
	{
>>>>>>> master
		aux = aux->next;
		i++;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	aux = *env_list;
	i = 0;
<<<<<<< HEAD
	while (aux == NULL && i)
=======
	while (aux != NULL)
>>>>>>> master
	{
		envp[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
