/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:43:55 by jvacaris          #+#    #+#             */
/*   Updated: 2022/01/02 17:52:40 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <termios.h>
# include "libft.h"
# include "errors.h"
# include "constants.h"

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}t_str;

typedef struct s_red
{
	int				pip_in;
	int				pip_out;
	char			*path;
	char			**params;
	char			**redirs;
	struct s_red	*next;
}t_red;

typedef struct s_var
{
	t_str	*env;
	int		last_cmd_status;
	int		waitedheredoc;
}t_var;

t_var	g_var;

//*		builtins / cd.c
void	ft_cd(t_str **env_list, char **argv);

//*		builtins / echo.c
void	ft_echo(char **list);

//*		builtins / exit.c
void	ft_exit(t_str **env_list, char **argv);

//*		builtins / env.c
void	init_ms_env(char **env_vector, t_str **env_list);
void	ft_env(t_str **env_list, char **argv);
char	*ft_getenv(t_str **env_list, const char *str);

//*		builtins / export.c
void	ft_export(t_str **env_list, char **argv);

//*		builtins / pwd.c
void	ft_pwd(t_str **env_list, char **argv);

//*		builtins / unset.c
void	ft_unset(t_str **env_list, char **argv);

//		old / exec_command.c
//// void	exec_command(char **list, char **envp);

//		interpreter.c
//// void	interpreter(char **list, t_str **env_list);

//		old / modifsplit.c
//// int		ft_modstrcpy(char *orgn, char **end, int len);
//// char	**modifsplit(char *input);

//		old / old_var_expansor.c
//// char	*getvarvalue(char *str);
//// void	expand_var(char *orgn, char **end, int *a, int *b);
//// void	dollarfound_getlen(int *a, int *count, char *input);
//// char	*recursive_expand(char *str, t_str **env_list);

//		old / ft_modstrcmp.c
//// int		modstrcmp(char *str1, char *str2);

//*		utils / error_handler.c
void	log_error(char *str_error, int status_error);
void	log_error_free(char *malloc_str_error, int status_error);
int		max_pipes_exceeded(char **tokens);
void	translate_number(int nbr);
void	ft_search_word( char *to_find);

//*		utils / ft_is_it_directory.c
int		ft_is_directory(char *path);

//*		utils / ft_strslashjoin.c
char	*ft_strslashjoin(char const *s1, char const *s2);

//*		utils / is_valid_var.c
int		is_valid_var(char prv_char, char curr_char, char nxt_char, char qm);
int		is_valid_var_hd(char *str, int idx);

//*		utils / lst_red_handler.c
void	lst_red_add_front(t_red **list, t_red *new);
void	lst_red_add_back(t_red **list, t_red *new);
t_red	*lst_red_new(void);
void	lst_red_free(t_red **list);
void	lst_red_print(t_red *list);

//*		utils / lst_str_handler.c
void	lst_str_add_sorted(t_str **list, char *str);
void	lst_str_free(t_str **list);
void	lst_str_print(t_str *list);
void	lst_str_delete(t_str **list, char *str, size_t len);

//*		utils / lst_str_handler2.c
void	lst_str_add_front(t_str **list, char *str);
void	lst_str_add_back(t_str **list, char *str);
t_str	*lst_str_get_str(t_str **list, const char *str);
char	**lst_str_to_array(t_str **env_list);

//*		utils / megafree.c
void	megafree(char ***list);
void	array_str_print(char **array);
int		array_str_get_size(char **array);

//*		utils / qm_remover.c
char	*adv_qm_rem(char *qm_str, int b_free);

//*		utils / token_handler.c
char	**get_tokens(char *input);
int		has_token(const char *input);

//*		utils / token_handler2.c
int		eval_tokens(const char *token, char **path);
int		has_pipe_redir_open(char **array);

//*		utils / signal_handler.c
void	signal_handler_forks(int is_children);
void	signal_handler_default(void);

//*		command_sorter.c
void	new_exec_command(t_red *red_node, char **env, int bool_addexit);
void	command_sorter_no_pipes(t_red *red_node, char **env, int fdi, int fdo);
void	command_sorter_wth_pipes(t_red *red_node, char **env);

//*		heredoc.c
void	ft_heredoc_qm(int *fdi, char *last_line, int orig_fds[2]);
void	ft_heredoc(int *fdi, char *last_line, int orig_fds[2]);

//*		minishell1.c
//?		(main)

//*		new_redirections.c
void	new_redirections(char **list, t_str **env_list);

//*		qm_error_detector.c
int		qm_error_detector(char *str);

//*		red_struct_filler.c
int		put_params_in_struct(char **list, t_str **env_list, t_red **red_list);
char	*new_getpath(char *raw_cmd, t_str **env_list);

//*		var_expansor.c
char	*recursive_expand(char *malloc_str, t_str **env_list);

char	*recursive_close_quotes(char *str_got_old);
void	get_heredocs(char **input);
#endif
