#include "minishell.h"

/**
 * * Handle SIGINT signal CTRL+C, promping new Line
 * @param signal	signal identifier (see man signal)
*/
static void	ft_signal_handler(int signal)
{
	(void)signal;
	//TODO handle when there is some text
	write(1, MS_PROMPT_SIG_INT, ft_strlen(MS_PROMPT_SIG_INT));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * * Replace a set of characters on a string starting at some index
 * @param str		string to modify 
 * @param charset	set of characters to replace
 * @param index		starting point of replacing
*/
char	*ft_replace(char *str, char const *oldset, char const *newset)
{
	char	*out;
	int		index;
	int		index_needle_on_haystack;
	size_t	len;
	char	*strnstr;
	size_t	old_set_len;

	index = -1;
	len = ft_strlen(str);
	old_set_len = ft_strlen(oldset);
	index_needle_on_haystack = ft_strnstr(str, oldset, len)  - str; 
	out = malloc(sizeof(char) * (len - old_set_len + ft_strlen(newset) + 1));
	while (str[++index] != '\0')
		out[index] = str[index];	
	index = strnstr - str;
	index = -1;
	while (newset[++index] != '\0')
		out[index_needle_on_haystack + index] = newset[index];
	free(str);
	out[index] = '\0';
	return (out);
}

	// if (curr_char == '$' && prv_char != '\\' && \
	// (ft_isalnum(nxt_char) || nxt_char == '_') && (qm == '"' || !qm))

static void	ft_expanse_var(char **argv, t_str **env_list)
{
	int		i;
	char	*strchr_$;
	char 	*tmp;
	size_t	len;
	t_str 	*aux;

	i = 0;
	while (argv[i] != 0)
	{
		strchr_$ = ft_strchr(argv[i], '$'); 
		while (strchr_$ != NULL && strchr_$[-1] == '\\' && (ft_isalnum(strchr_$[1]) || strchr_$[1] == '_'))
			strchr_$ = ft_strchr(strchr_$, '$');
		printf("%s\n", strchr_$);
		if (!strchr_$)
			i++;
		else
		{
			len = 1;
			while (ft_isalnum(strchr_$[len]))
				len++;
			printf("2 %s\n", strchr_$);
			tmp = ft_substr(strchr_$, 1, len);
			printf("3 %s\n", tmp);
			aux = ft_lst_str_get_str(env_list, tmp);
			//printf("4 %s\n", aux->str);
			if (aux != NULL)
				argv[i] = ft_replace(argv[i], aux->str,strchr_$ - argv[i]);
			else
				argv[i] = ft_replace(argv[i], "", strchr_$ - argv[i]);
			printf("5 %s\n", argv[i]);
			free(tmp);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str_got;
	char	**param_list;
	t_str	*env_list;

	(void)argc;
	(void)argv;
//	printf("\nhye\n");
	env_list = NULL;
	init_ms_env(env, &env_list);
	ft_array_str_print(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_signal_handler);
	while (1)
	{
		str_got = readline(MS_PROMPT);
		if (str_got == NULL)
		{
			printf(MSG_EXIT); //TODO write exit at console input's level
			exit(0);
		}
		if (*str_got != '\0' )
			add_history(str_got);
		if (qm_error_detector(str_got))
			write(1, "Error: quotation marks not properly closed!\n", 44);
		else
		{
			param_list = modifsplit(str_got);
			ft_expanse_var(param_list, &env_list);
			interpreter(param_list, &env_list);
		}
		free(str_got);
//		system("lsof -c minishell");
	}
	return (0);
}
