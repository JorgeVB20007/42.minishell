/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:32:31 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/31 15:29:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENDTOKEN "|<>\0"

/**
 * * Add redirection token to the list
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				input's processed characters
*/
static int	add_redir_token(t_str **list, const char *input)
{
	if (input[0] != input[1])
	{
		if (input[0] == '>')
			lst_str_add_back(list, ft_strdup(">"));
		else
			lst_str_add_back(list, ft_strdup("<"));
		return (1);
	}
	else
	{
		if (input[0] == '>')
			lst_str_add_back(list, ft_strdup(">>"));
		else
			lst_str_add_back(list, ft_strdup("<<"));
		return (2);
	}
	return (0);
}

/**
 * * Validates str to add to token list, avoiding empty expansions problems
 * @param token_list	token list to populate
 * @param malloc_str	malloced str to validate
*/
static void	try_add_default_token(t_str **list, char *malloc_str)
{
	t_str	*aux;
	char	*tmp;

	aux = *list;
	if (aux != NULL)
		while (aux->next != NULL)
			aux = aux->next;
	if (!aux || (aux->str[0] != '<' && aux->str[0] != '>'))
	{
		tmp = adv_qm_rem(ft_expand(malloc_str), FREE);
		if (!ft_strcmp(tmp, "\0"))
			ft_free((void **)&malloc_str);
		ft_free((void **)&tmp);
	}
	if (malloc_str != NULL)
		lst_str_add_back(list, malloc_str);
}

/**
 * * Add default token to the list
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				input's processed characters
*/
static size_t	add_default_token(t_str **list, const char *input)
{
	char	*s;
	int		quotes;

	s = (char *)input;
	quotes = NONE;
	while (1)
	{
		if (quotes == NONE && (ft_isspace(*s) || ft_strchr(ENDTOKEN, *s)))
			break ;
		else if (quotes == NONE && *s == '\'')
			quotes = SINGLE;
		else if (quotes == SINGLE && *s == '\'')
			quotes = NONE;
		else if (quotes == NONE && *s == '\"')
			quotes = DOUBLE;
		else if (quotes == DOUBLE && *s == '\"')
			quotes = NONE;
		s++;
	}
	try_add_default_token(list, ft_substr(input, 0, s - input));
	return (s - input);
}

/**
 * * Get tokenlist from and input string
 * * Token is the minimun divisible item to handle on MiniShell
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				List of tokens
*/
static void	recursive_get_token_list(t_str **token_list, char **input)
{
	while (ft_isspace(**input))
		*input += 1;
	if (**input == '|')
	{
		lst_str_add_back(token_list, ft_strdup("|"));
		*input += 1;
	}
	else if (ft_strchr("<>", **input))
		*input += add_redir_token(token_list, *input);
	else
		*input += add_default_token(token_list, *input);
	while (ft_isspace(**input))
		*input += 1;
	if (**input != '\0')
		recursive_get_token_list(token_list, input);
}

/**
 * * Get tokens from and input string
 * * Token is the minimun divisible item to handle on MiniShell
 * @param input	input to tokenize
 * @return 		array of tokens
*/
char	**get_token_list(char *input)
{
	t_str	*token_list;
	char	**result;

	if (*input == '\0')
		return (NULL);
	token_list = NULL;
	ft_rand_eight_module(input);
	recursive_get_token_list(&token_list, &input);
	result = lst_str_to_array(&token_list);
	lst_str_free(&token_list);
	if (max_pipes_exceeded(result))
	{
		g_var.current_status = 1;
		megafree(&result);
		return (NULL);
	}
	return (result);
}
