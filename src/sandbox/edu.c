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

// int countpipes(char **tokens)
// {

// 	int		pipes;

// 	pipes = 0;
// 	while (*tokens != NULL && pipes < INT_MAX)
// 		if (!ft_strcmp(*tokens++, "|"))
// 			pipes++;
// }
enum e_pipe_fd
{
	READ_END,
	WRITE_END
};

typedef struct s_fd{
	int	fd[2];
}t_fd;

void close_forkedpipes( int pipes, pid_t *pids, t_fd *fds)
{
	int		status;
	int		i;
	int 	j;

	//status = (int *)malloc(sizeof(int) * pipes);
	i = -1;
	while (++i < pipes)
	{
		j = -1;
		while (++j < pipes - 1 && pids[i] != 0)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
		waitpid(pids[i], &status, 0);
	}
	free(pids);
	free(fds);
}

void create_forkedpipes(int pipes)
{
	pid_t	*pids;
	t_fd	*fds;
	int		i;
	int		j;

	pids = (pid_t *)malloc(sizeof(pid_t) * pipes);
	fds = (t_fd *)malloc(sizeof(t_fd) * pipes - 1);
	i = -1;
	while (++i < pipes - 1)
		pipe(fds[i].fd);
	i = -1;
	while (++i < pipes)
	{
		pids[i] = fork();
		//signal_handler_forks(pids[i]);
		if (i != pipes - 1 && pids[i] == 0)
			dup2(fds[i].fd[1], STDOUT_FILENO);
		if (i != 0 && pids[i] == 0)
			dup2(fds[i - 1].fd[0], STDIN_FILENO);
		j = -1;
		while (++j < pipes - 1 && pids[i] == 0)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
	}
	if (pids[0] == 0)
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	if (pids[1] == 0)
		execlp("grep", "grep", "rtt", NULL);
	if (pids[2] == 0)
		execlp("wc", "wc", NULL);
	close_forkedpipes(pipes, pids, fds);

}

int main(void)
{
	create_forkedpipes(3);
}
