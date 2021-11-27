/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:43:55 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/27 21:38:45 by jvacaris         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
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

t_str	 *g_env;

// char	**modifsplit(char *input);
char	**get_tokens(char *input);
// void	dollarfound_getlen(int *a, int *count, char *input);
// void	expand_var(char *orgn, char **end, int *a, int *b);
// int		ft_modstrcpy(char *orgn, char **end, int len);
void	interpreter(char **list, t_str **env_list);
void	ft_echo(char **list);
int		qm_error_detector(char *str);
void	init_ms_env(char **env_vector, t_str **env_list);
char	**lst_str_to_array(t_str **env_list);
void	lst_str_free(t_str **list);
void	lst_str_print(t_str *list);
void	lst_str_add_back(t_str **list, char *str);
void	lst_str_add_front(t_str **list, char *str);
void	lst_str_add_sorted(t_str **list, char *str);
void	lst_str_delete(t_str **list, char *str, size_t len);
t_str	*lst_str_get_str(t_str **list, const char *str);
void	exec_command(char **list, char **envp);
char	*ft_strslashjoin(char const *s1, char const *s2);
void	megafree(char ***list);
void	ft_pwd(t_str **env_list, char **argv);
void	ft_env(t_str **env_list, char **argv);
void	ft_unset(t_str **env_list, char **argv);
void	ft_export(t_str **env_list, char **argv);
int		is_valid_var(char prv_char, char curr_char, char nxt_char, char qm);
int		is_valid_var_hd(char *str, int idx);
char	*adv_qm_rem(char *qm_str, int b_free);
void	ft_cd(t_str **env_list, char **argv);
void	ft_heredoc(int *fdi, char *last_line);
void	ft_heredoc_qm(int *fdi, char *last_line);
void	ft_array_str_print(char **array);
// char	*getvarvalue(char *str);
int		modstrcmp(char *str1, char *str2);
char	*ft_getenv(t_str **env_list, const char *str);
void	new_redirections(char **list, t_str **env_list);
void	lst_red_free(t_red **list);
t_red	*lst_red_new(void);
void	lst_red_add_back(t_red **list, t_red *new);
void	lst_red_add_front(t_red **list, t_red *new);
void	new_exec_command(t_red *red_node, char **env);
void	lst_red_print(t_red *list);

int		has_last_redirection_open(const char *str);
int		has_pipe_redir_open(char **array);
char	*recursive_expand(char *str, t_str **env_list);
#endif
