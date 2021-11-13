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
	char 	*tmp;
	size_t	len;
	char	*strnstr;

	len = ft_strlen(str);
	strnstr = ft_strnstr(str, oldset, len);
	out = ft_substr(str, 0, strnstr - str);
	tmp = ft_strjoin(out, newset);
	free(out);
	out = ft_strjoin(tmp, strnstr + ft_strlen(oldset));
	free(tmp);
	return (out);
}

static char *get_valid_ft_strchr_$(const char *str)
{
	char	*strchr_$;

	strchr_$ = (char *)str;
	while (1)
	{
		strchr_$ = ft_strchr(strchr_$, '$');
		if (!strchr_$)
			return (NULL);
		if (strchr_$ == str)
			return (strchr_$);
		if (strchr_$[-1] != '\\')
			return (strchr_$);
	}
}

static void	ft_expanse_var(char **argv, t_str **env_list)
{
	int		i;
	char	*strchr_$;
	char 	*tmp;
	size_t	len;
	t_str 	*aux;

	i = 0;
	strchr_$ = NULL;
	while (argv[i] != 0)
	{
		strchr_$ = get_valid_ft_strchr_$(argv[i]);
		// strchr_$ = ft_strchr(argv[i], '$');
		if (!strchr_$)
			i++;
		else
		{
			len = 1;
			while (ft_isalnum(strchr_$[len]))
				len++;
			tmp = ft_substr(strchr_$, 0, len);
			aux = ft_lst_str_get_str(env_list, &tmp[1]);
			if (aux != NULL)
				argv[i] = ft_replace(argv[i], tmp, ft_strchr(aux->str, '=') + 1);
			else
				argv[i] = ft_replace(argv[i], tmp, "");
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
