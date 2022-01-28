/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:17:59 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/28 20:41:15 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXPAND_HOME "$HOME"
#define EXPAND_PWD "$PWD"
#define EXPAND_OLDPWD "$OLDPWD"

char	*expanse_tilde(const char *str)
{
	char	*aux;
	t_str	*env;

	aux = NULL;
	env = NULL;
	if (!ft_strcmp(str, "~") || !ft_strncmp(str, "~/", 2))
		aux = ft_strreplaceat(str, "~", EXPAND_HOME, 0);
	else if (!ft_strcmp(str, "~+") || !ft_strncmp(str, "~+/", 3))
	{
		env = lst_str_get_str(&g_var.env, LIT_PWD_LIKE);
		if (!aux && env != NULL)
			aux = ft_strreplaceat(str, "~+", EXPAND_PWD, 0);
	}
	else if (!ft_strcmp(str, "~-") || !ft_strncmp(str, "~-/", 3))
	{
		env = lst_str_get_str(&g_var.env, LIT_OLDPWD_LIKE);
		if (!aux && env != NULL)
			aux = ft_strreplaceat(str, "~-", EXPAND_OLDPWD, 0);
	}
	if (!aux && !env)
		aux = ft_strdup(str);
	return (aux);
}

static void	split_expanded_token(char *str_expanded, t_str **expanded_tokens)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str_expanded, ' ');
	while (split[i] != NULL)
	{
		if (eval_token_redir(split[i]) != NONE)
			lst_str_add_back(expanded_tokens, ft_strjoin(split[i], "$$$"));
		else
			lst_str_add_back(expanded_tokens, ft_strdup(split[i]));
		i++;
	}
	free(str_expanded);
	megafree(&split);
}

static void	expand_token(t_str *prev, t_str *token, t_str **expanded_tokens)
{
	char	*str_expanded;
	int		type_token;
	int		type_prev;

	type_prev = eval_token_redir(prev->str);
	type_token = eval_token_redir(token->str);
	str_expanded = NULL;
	if (type_token != NONE)
		lst_str_add_back(expanded_tokens, ft_strdup(token->str));
	else
	{
		str_expanded = adv_qm_rem(ft_expand(token->str, NOT_HEREDOC), TRUE);
		if (type_prev != NONE && type_prev != PIPE && type_prev != HEREDOC)
			if (!ft_strcmp(str_expanded, ""))
				ft_free((void **) &str_expanded);
		if (str_expanded == NULL)
			lst_str_add_back(expanded_tokens, ft_strdup(token->str));
		else if (ft_strchr(str_expanded, ' '))
			split_expanded_token(str_expanded, expanded_tokens);
		else
			lst_str_add_back(expanded_tokens, str_expanded);
	}
}

char	**expand_tokens(t_str	*token)
{
	t_str	*expanded_tokens;
	char	**result;

	expanded_tokens = NULL;
	lst_str_add_front(&token, "empty");
	if (token->next != NULL)
	{
		while (token->next != NULL)
		{
			expand_token(token, token->next, &expanded_tokens);
			token = token->next;
		}		
	}
	result = lst_str_to_array(&expanded_tokens);
	return (result);
}
