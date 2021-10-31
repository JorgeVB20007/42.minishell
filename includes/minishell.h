#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <sys/param.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "errors.h"
# include "constants.h"

char	**modifsplit(char *input);
void	dollarfound_getlen(int *a, int *count, char *input);
void	expand_var(char *orgn, char **end, int *a, int *b);
int		ft_modstrcpy(char *orgn, char **end, int len);
void	interpreter(char **list);
void	ft_echo(char **list, int *idx);
char	*adv_qm_rem(char *qm_str);
void	get_default_env(char **env);
void	print_env_list(char **env_list);
void	ft_pwd(void);
#endif