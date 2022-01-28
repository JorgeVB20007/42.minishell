/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:08:30 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/28 19:28:22 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/**
 * * Add from a expanded token wich coulf be splited in several inputs
 * @param str_expanded	token expanded to process
 * @param process		current process to initialize
*/
static void	add_expanded_splited_tokens(char *str_expanded, t_p	*process)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str_expanded, ' ');
	while (split[i] != NULL)
	{
		if (process->type == NONE)
		{
			process->type = eval_token_non_redir(split[i]);
			if (process->type == TEXT)
				process->status = g_var.current_status;
			else if (process->type == COMMAND)
				process->pathname = new_getpath(split[i]);
		}
		lst_str_add_back(&process->args, ft_strdup(split[i]));
		i++;
	}
	free(str_expanded);
	megafree(&split);
}

/**
 * * Add redirection info to current process
 * @param token			current token to read from
 * @param process		current process to initialize
 * @param type_redir	redirection type
*/
static void	add_redir_to_process(const char *token, t_p *process, \
int type_redir)
{
	t_redirection	*r;
	char			*no_quotes_token;

	no_quotes_token = NULL;
	if (token != NULL)
	{
		r = lst_redir_new();
		r->type = type_redir;
		if (type_redir != HEREDOC)
			r->go_to = ft_strdup(token);
		else
		{
			no_quotes_token = adv_qm_rem((char *)token, NOT_FREE);
			r->go_to = get_heredoc_pipedfork(no_quotes_token);
			if (!ft_strcmp(r->go_to, no_quotes_token))
				g_var.current_status = 130;
			if (!ft_strcmp(r->go_to, ""))
				ft_free((void **)&r->go_to);
			else if (!ft_strchr(token, '\'') && !ft_strchr(token, '\"'))
				r->go_to = ft_expand_heredoc(r->go_to);
			free(no_quotes_token);
		}
		lst_redir_add_back(&process->redir, r);
	}
}

/**
 * * Add exec info (cmd,builtin...) to current process
 * @param token		current token to read from
 * @param process	current process to initialize
 * @param id_argv	current argv id to save
*/
static void	add_exec_info_to_process(const char *token, t_p *process)
{
	char	*str;

	str = adv_qm_rem(ft_expand(token), FREE);
	if (process->type != NONE)
		lst_str_add_back(&process->args, str);
	else
	{
		if (ft_strchr(str, ' ') && ft_strchr(token, '$'))
			add_expanded_splited_tokens(str, process);
		else
		{
			process->type = eval_token_non_redir(str);
			if (process->type == TEXT)
				process->status = g_var.current_status;
			else if (process->type == COMMAND)
				process->pathname = new_getpath(str);
			lst_str_add_back(&process->args, str);
		}
	}
}

/**
 * * Init process with needed info to execute later
 * @param tokens	current tokens list
 * @param process	current process to initialize
*/
static void	init_process(char **tokens, t_p	*process)
{
	int		type_redir;

	while (*tokens != NULL && ft_strcmp(*tokens, "|"))
	{
		type_redir = eval_token_redir(*tokens);
		if (type_redir != NONE)
			add_redir_to_process(*(++tokens), process, type_redir);
		else
			add_exec_info_to_process(*tokens, process);
		if (g_var.current_status == 130)
			break ;
		tokens++;
	}
	process->argv = lst_str_to_array(&process->args);
}

/**
 * * Returns processes to handle with pipes
 * * Every process has needed info to execute later
 * @param tokens	tokens list
 * @param processes	list of process to return
*/
void	get_processes(char **tokens, t_p **processes)
{
	t_p	*process;

	g_var.current_status = NONE;
	while (*tokens != NULL && g_var.current_status != 130)
	{
		if (!ft_strcmp(*tokens, "|"))
			tokens++;
		process = NULL;
		process = lst_process_new();
		init_process(tokens, process);
		lst_process_add_back(processes, process);
		while (*tokens != NULL && ft_strcmp(*tokens, "|"))
			tokens++;
	}
	if (g_var.current_status == 130)
		lst_process_free(processes);
}
