/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:43:55 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/01 07:39:18 by emadriga         ###   ########.fr       */
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
# include "constants.h"

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}t_str;

typedef struct s_var
{
	t_str	*env;
	int		current_status;
	int		last_status;
	int		waitedheredoc;
	size_t	rng;
	int		elephants;
}t_var;

typedef struct s_redirection{
	int						type;
	char					*go_to;
	struct s_redirection	*next;
}t_redirection;

typedef struct s_process{
	int						type;
	int						status;
	char					*pathname;
	char					**argv;
	t_str					*args;
	t_redirection			*redir;
	struct s_process		*next;
}t_p;

typedef struct s_fd{
	int	fd[2];
}t_fd;

t_var	g_var;

//*		builtins / builtins.c
void			ft_builtins(char **argv);

//*		builtins / cd.c
void			ft_cd(char **argv);

//*		builtins / echo.c
void			ft_echo(char **list);

//*		builtins / env.c
void			init_ms_env(char **env_vector, t_str **env_list);
void			ft_env(char **argv);
char			*ft_getenv(const char *str);

//*		builtins / exit.c
void			ft_exit(char **argv);

//*		builtins / export.c
void			ft_export(char **argv);

//*		builtins / pwd.c
void			ft_pwd(char **argv);

//*		builtins / unset.c
void			ft_unset(char **argv);

//*		expansions / var_expansor.c
char			*ft_expand(const char *str);
char			*recursive_expand(char *malloc_str, int is_heredoc);

//*		expansions / var_expansor2.c
char			*expanse_tilde(const char *str);
char			*ft_expand_heredoc(char *maloc_str);

//*		forks / close_quotes.c
char			*close_quotes_pipedfork(char *str_got_old);

//*		forks / heredoc_handler.c
void			get_heredoc_list(char **input, t_str **heredoc_list);
char			*get_heredoc_pipedfork(const char *key);

//*		processes / get_processes.c
void			get_processes(char **tokens, t_p **processes);

//*		processes / process_redirections.c
void			process_redirections(t_redirection *r);

//*		processes / run_processes.c
void			run_processes(t_p **processes, int pipes);

//*		utils / error_handler.c
void			log_error(char *str_error, int status_error);
void			log_error_free(char *malloc_str_error, int status_error);
void			execve_sleep(char **usleep_argv);
int				count_pipes(char **tokens);
int				ft_rand_eight_module(const char *str);

//*		utils / error_handler2.c
int				max_pipes_exceeded(char **tokens);
void			ft_search_word(char *to_find, char **sleep_argv);

//*		utils / error_handler3.c
void			translate_number(int nbr, char **sleep_argv);

//*		utils / ft_is_it_directory.c
int				ft_is_directory(const char *path);

//*		utils / ft_strslashjoin.c
char			*ft_strslashjoin(char const *s1, char const *s2);

//*		utils / is_it_path.c
int				is_it_path(char *str);

//*		utils / lst_process_handler.c
void			lst_process_add_front(t_p **list, t_p *new);
void			lst_process_add_back(t_p **list, t_p *new);
t_p				*lst_process_new(void);
void			lst_process_free(t_p **list);
void			lst_process_print(t_p *list);

//*		utils / lst_redir_handler.c
void			lst_redir_add_front(t_redirection **list, t_redirection *new);
void			lst_redir_add_back(t_redirection **list, t_redirection *new);
t_redirection	*lst_redir_new(void);
void			lst_redir_free(t_redirection **list);
void			lst_redir_print(t_redirection *list);

//*		utils / lst_str_handler.c
void			lst_str_add_sorted(t_str **list, char *str);
void			lst_str_free(t_str **list);
void			lst_str_print(t_str *list);
void			lst_str_delete(t_str **list, char *str, size_t len);

//*		utils / lst_str_handler2.c
void			lst_str_add_front(t_str **list, char *str);
void			lst_str_add_back(t_str **list, char *str);
t_str			*lst_str_get_str(t_str **list, const char *str);
char			**lst_str_to_array(t_str **list);

//*		utils / megafree.c
void			megafree(char ***list);
void			array_str_print(char **array);
int				array_str_get_size(char **array);

//*		utils / quote_mark_handler.c
char			*adv_qm_rem(char *qm_str, int b_free);
int				qm_error_detector(char *str);

//*		utils / signal_handler.c
void			signal_handler_forks(int is_children);
void			signal_handler_default(void);
void			signal_handler_elephants_sigint(int signal);
void			signal_handler_process_sigint(int signal);

//*		utils / token_handler.c
char			**get_token_list(char *input);

//*		utils / token_handler2.c
int				eval_token_redir(const char *token);
int				eval_token_non_redir(const char *token);
int				has_pipe_redir_open(char **array);
int				has_token(const char *input);

//*		get_path.c
char			*new_getpath(char *raw_cmd);

#endif
