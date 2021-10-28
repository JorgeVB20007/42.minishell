#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "errors.h"

int		main(void);
char	**modifsplit(char *input);
void	dollarfound_getlen(int *a, int *count, char *input);
void	expand_var(char *orgn, char **end, int *a, int *b);
int		ft_modstrcpy(char *orgn, char **end, int len);
void	interpreter(char **list);
void	ft_echo(char **list, int *idx);

#endif