/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:42:55 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/23 21:50:36 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PRINT_DECLARE_SIMPLE "declare -x %s\n"
#define PRINT_DECLARE_COMPLEX "declare -x %.*s\"%s\"\n"
#define EXPORT_WRONG_ID "export: `{0}': not a valid identifier\n"

/**
 * * Evals vallid export to add
 * @param str	enviroment list
*/
static int	is_valid_add_export(const char *str)
{
	char	*aux;
	int		has_like;
	int		ok;

	aux = (char *)str;
	has_like = 0;
	ok = ft_isalpha(*aux++);
	while (*aux != '\0' && !has_like && ok == 1)
	{
		if (!ft_isalnum(*aux) && !ft_strchr("=\"", *aux))
			ok = 0;
		if (*aux == '=')
			has_like = 1;
		aux++;
	}
	--aux;
	if (!ok)
		log_error_free(ft_strreplace(EXPORT_WRONG_ID, "{0}", str), 1);
	return (ok);
}

/**
 * * Print ENV list
 * @param env_list	enviroment list
*/
static void	ft_print_env_without_last_cmd(t_str **env_list)
{
	t_str	*aux;
	char	*strchr;
	int		width;
	char	*strchr_replaced;

	aux = *env_list;
	while (aux != NULL)
	{
		if (ft_strncmp(aux->str, "_=/", 3))
		{
			strchr = ft_strchr(aux->str, '=');
			if (strchr != NULL)
			{
				strchr++;
				strchr_replaced = ft_strreplace(strchr, "\"", "\\\"");
				width = (int)(strchr - aux->str);
				printf(PRINT_DECLARE_COMPLEX, width, aux->str, strchr_replaced);
				free(strchr_replaced);
			}
			else
				printf(PRINT_DECLARE_SIMPLE, aux->str);
		}
		aux = aux->next;
	}
}

/**
 * * Add str to enviroment variables list (alphabetically-sorted)
 * * if str exist updates value
 * @param env_list	enviroment list
 * @param str		str to add
*/
static void	ft_export_add(t_str **env_list, char *str)
{
	char	*env_desc;
	char	*strchr;

	env_desc = NULL;
	strchr = ft_strchr(str, '=');
	if (strchr)
	{
		env_desc = ft_substr(str, 0, strchr - str + 1);
		lst_str_delete(env_list, env_desc, strchr - str + 1);
		free(env_desc);
		env_desc = ft_substr(str, 0, strchr - str);
	}
	else
		env_desc = ft_strdup(str);
	lst_str_delete(env_list, env_desc, ULONG_MAX);
	if (!ft_strcmp(ft_getenv(env_desc), ""))
		lst_str_add_sorted(env_list, str);
	free(env_desc);
}

/**
 * * This should recreate the bash funtion "export".
 * * Returns ENV alphabetically-sorted
 * * Add records (through argumment vector) to enviroment variables list
 * @param argv	vector of arguments containing records to add
*/
void	ft_export(char **argv)
{
	int		i;
	char	*argv_without_qm;

	i = 1;
	argv_without_qm = NULL;
	if (argv[i] == NULL)
		ft_print_env_without_last_cmd(&g_var.env);
	while (argv[i] != NULL)
	{
		if (is_valid_add_export(argv[i]))
		{
			argv_without_qm = adv_qm_rem(argv[i], NOT_FREE);
			ft_export_add(&g_var.env, argv_without_qm);
		}
		i++;
	}
}
