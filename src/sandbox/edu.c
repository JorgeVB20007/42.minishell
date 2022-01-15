#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <termios.h>

enum e_pipe_fd
{
	READ_END,
	WRITE_END
};

typedef struct s_fd{
	int	fd[2];
}t_fd;

static void	close_forkedpipes( int pipes, pid_t *pids, t_fd *fds)
{
	int		status;
	int		i;
	int		j;

	i = -1;
	while (++i < pipes)
	{
		j = -1;
		while (++j < pipes - 1 && pids[i] != 0 && i == 0)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
		waitpid(pids[i], &status, 0);
	}
	free(pids);
	free(fds);
}

static void	initson(int pipes, pid_t *pids, t_fd *fds, int i)
{
	int	j;

	if (pids[i] == 0)
	{
		if (i != pipes - 1)
			dup2(fds[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(fds[i - 1].fd[0], STDIN_FILENO);
		j = -1;
		while (++j < pipes - 1 && pids[i] == 0)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
		if (pids[0] == 0 && i == 0)
			execlp("ls", "ls", "-la", NULL);
		if (pids[1] == 0 && i == 1)
			execlp("sort", "sort", NULL);
		if (pids[2] == 0 && i == 1)
			execlp("grep", "grep", "src", NULL);
		if (pids[3] == 0)
			execlp("wc", "wc", NULL);
	}
}

static void	create_forkedpipes(int pipes)
{
	pid_t	*pids;
	t_fd	*fds;
	int		i;

	pids = (pid_t *)malloc(sizeof(pid_t) * pipes);
	fds = (t_fd *)malloc(sizeof(t_fd) * pipes - 1);
	i = -1;
	while (++i < pipes - 1)
		pipe(fds[i].fd);
	i = -1;
	while (++i < pipes)
	{
		pids[i] = fork();
		initson(pipes, pids, fds, i);
	}
	close_forkedpipes(pipes, pids, fds);
}

//gcc -Wall -Wextra -Werror -g3 -fsanitize=address -pedantic src/sandbox/edu.c -o sandboxtest && ./sandboxtest && rm -rf  sandboxtest*
int	main(void)
{
	create_forkedpipes(4);
}
