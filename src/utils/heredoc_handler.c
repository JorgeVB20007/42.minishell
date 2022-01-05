#include "minishell.h"

static char	*ft_strjoin_freedouble(char *s1, char *s2)
{
	char	*join;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = ft_calloc(sizeof(char), len);
	if (!join)
		return (0);
	ft_strlcat(join, s1, len);
	ft_strlcat(join, s2, len);
	free(s1);
	free(s2);
	return (join);
}

/**
 * * Handle unclosed quotes waiting STDIN_FILENO to close them
 * @param str	current STDIN_FILENO input
*/
static char	*recursive_close_quotes(char *str)
{
	int		i;
	int		quotes;
	char	*out;

	i = 0;
	out = str;
	quotes = NONE;
	while (str[i] != '\0')
	{
		if (quotes == NONE && str[i] == '\'')
			quotes = SINGLE;
		else if (quotes == SINGLE && str[i] == '\'')
			quotes = NONE;
		else if (quotes == NONE && str[i] == '\"')
			quotes = DOUBLE;
		else if (quotes == DOUBLE && str[i] == '\"')
			quotes = NONE;
		i++;
	}
	if (quotes != NONE)
		out = recursive_close_quotes(ft_strjoin_freedouble(str, \
			ft_strjoin_freedouble(ft_strdup("\n"), readline(">"))));
	return (out);
}

char	*close_quotes(char *str)
{
	t_pipedfork	t;
	char		buff[SHRT_MAX];

	pipe(t.fd);
	t.pid = fork();
	signal_handler_forks(!t.pid);
	if (!t.pid)
	{
		close(t.fd[0]);
		str = recursive_close_quotes(ft_strdup(str));
		write(t.fd[1], str, ft_strlen(str));
		close(t.fd[1]);
		exit(0);
	}
	else
	{
		close(t.fd[1]);
		read(t.fd[0], buff, SHRT_MAX);
	}
	free(str);
	waitpid(t.pid, &t.status, 0);
	signal_handler_default();
	if (WIFSIGNALED(t.status))
		return ("\0");
	return (ft_strdup(buff));
}

/**
 * * Get matching key heredoc from STDIN_FILENO
 * @param key	key to match with STDIN_FILENO
*/
static char	*get_heredoc(char *key)
{
	char	*line_read;
	char	*out;

	out = NULL;
	while (1)
	{
		line_read = readline(">");
		if (!ft_strcmp(key, line_read))
			break ;
		if (out != NULL)
			out = ft_strjoin_freedouble(out, \
			ft_strjoin_freedouble(ft_strdup("\n"), line_read));
		else
			out = line_read;
	}
	if (line_read != NULL)
		free(line_read);
	return (out);
}

/**
 * * Get heredoc list from token list with open heredocs
 * @param token_list	token list to go through looking for open heredoc
 * 						to retrieve
 * @return				List of heredocs
*/
void	get_heredoc_list(char **token_list)
{
	int		i;
	char	*heredoc;
	t_str	*heredocs_list;

	i = 0;
	heredocs_list = NULL;
	while (token_list[i] != NULL)
	{
		if (!ft_strcmp(token_list[i], "<<"))
		{
			heredoc = get_heredoc(token_list[i + 1]);
			lst_str_add_back(&heredocs_list, heredoc);
		}
		i++;
	}
	printf("\nHERDOCS\n");
	lst_str_print(heredocs_list);
	lst_str_free(&heredocs_list);
}
