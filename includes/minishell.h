/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:43:55 by jvacaris          #+#    #+#             */
/*   Updated: 2021/11/07 13:29:17 by emadriga         ###   ########.fr       */
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

char	**modifsplit(char *input);
void	dollarfound_getlen(int *a, int *count, char *input);
void	expand_var(char *orgn, char **end, int *a, int *b);
int		ft_modstrcpy(char *orgn, char **end, int len);
void	interpreter(char **list, t_str **env_list);
void	ft_echo(char **list);
char	*adv_qm_rem(char *qm_str);
int		qm_error_detector(char *str);
void	init_ms_env(char **env_vector, t_str **env_list);
void	ft_env(t_str **env_list, char **argv);
char	**env_list_to_vector(t_str **env_list);
void	ft_pwd(void);
void	ft_lst_str_free(t_str *list);
void	ft_lst_str_print(t_str *list);
void	ft_lst_str_add_back(t_str **list, char *str);
void	ft_lst_str_add_front(t_str **list, char *str);
void	ft_lst_str_add_sorted(t_str **list, char *str);
void	ft_lst_str_delete(t_str **list, char *str);
t_str	*ft_lst_str_get_str(t_str **list, const char *str);
void	exec_command(char **list, char **envp);
char	*ft_strslashjoin(char const *s1, char const *s2);
void	megafree(char ***list);
void	ft_unset(t_str **env_list, char **argv);
void	ft_export(t_str **env_list, char **argv);
void	ft_cd(t_str **env_list, char **argv);
#endif
