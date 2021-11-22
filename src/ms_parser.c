#include "minishell.h"

#define ENDTOKEN "|<>\0"

/**
 * * Add redirection token to the list
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				input's processed characters
*/
static int add_redir_token(t_str **list, const char *input)
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
 * * Add default token to the list
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				input's processed characters
*/
static size_t add_default_token(t_str **list,  const char *input)
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
	lst_str_add_back(list, ft_substr(input, 0, s - input));
	return (s - input);
}

/**
 * * Get tokenlist from and input string
 * * Token is the minimun divisible item to handle on MiniShell
 * @param token_list	token list to populate
 * @param input			input to tokenize
 * @return				List of tokens
*/
static void get_token_list(t_str **token_list, char **input)
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
	if (**input != '\0')
		get_token_list(token_list, input);
}

/**
 * * Get tokens from and input string
 * * Token is the minimun divisible item to handle on MiniShell
 * @param input	input to tokenize
 * @return 		array of tokens
*/
char	**get_tokens(char *input)
{
	t_str	*token_list;
	char	**result;

	token_list = NULL;
	get_token_list(&token_list, &input);
	result = lst_str_to_array(&token_list);
	return (result);
}
