/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:08:30 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/15 16:33:45 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/**
 * * Return size of argv's process to malloc  
 * @param token		current token to read from
*/
static int	get_process_argv_len(t_str *token)
{
	int		i;
	int		type_redir;

	i = 0;
	while (token != NULL && ft_strcmp(token->str, "|"))
	{
		type_redir = eval_token_redir(token->str);
		i += (type_redir == NONE);
		if (type_redir != NONE)
			token = token->next;
		token = token->next;
	}
	return (i);
}

/**
 * * Add redirection info to current process 
 * @param token			current token to read from
 * @param process		current process to initialize
 * @param type_redir	redirection type
*/
static void	add_redir_to_process(t_str *token, t_pp	*process, int type_redir)
{
	t_redir	*new;

	token = token->next;
	if (token != NULL)
	{	
		new = lst_redir_new();
		new->type = type_redir;
		new->go_to = ft_strdup(token->str);
		lst_redir_add_back(&process->redir, new);
	}
}

/**
 * * Init process with needed info to execute later
 * @param token		current token to read from
 * @param process	current process to initialize
*/
static void	init_piped_process(t_str *token, t_pp	*process)
{
	int		i;
	int		type_redir;

	process->argv = malloc(sizeof(char *) * (get_process_argv_len(token) + 1));
	process->argv[0] = adv_qm_rem(token->str, FALSE);
	if (process->is_cmd)
		process->pathname = new_getpath(process->argv[0], &g_var.env);
	i = 1;
	token = token->next;
	while (token != NULL && ft_strcmp(token->str, "|"))
	{
		process->argv[i] = ft_strdup(token->str);
		type_redir = eval_token_redir(token->str);
		if (type_redir != NONE)
			add_redir_to_process(token, process, type_redir);
		i += (type_redir == NONE);
		if (type_redir != NONE)
			token = token->next;
		token = token->next;
	}
	process->argv[i] = NULL;
}

/**
 * * Returns processes to handle with pipes
 * * Every process has needed info to execute later
 * @param tokens	tokens list
 * @param processes	list of process to return 
*/
void	get_piped_processes(t_str **tokens, t_pp **processes)
{
	t_pp	*process;
	int		type_token;
	t_str	*token;

	token = *tokens;
	while (token != NULL)
	{
		if (!ft_strcmp(token->str, "|"))
			token = token->next;
		type_token = eval_token(token->str);
		if (type_token != BUILTIN && type_token != COMMAND)
		{
			lst_piped_process_free(processes);
			return ;
		}
		process = NULL;
		process = lst_piped_process_new();
		process->is_cmd = type_token == COMMAND;
		init_piped_process(token, process);
		lst_piped_process_add_back(processes, process);
		while (token != NULL && ft_strcmp(token->str, "|"))
			token = token->next;
	}
}
