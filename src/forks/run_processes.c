/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:42 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/23 08:08:16 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_fd{
	int	fd[2];
}t_fd;

static void	close_forkedpipes(int pipes, pid_t *pids, t_fd *fds)
{
	int		status;
	int		i;
	int		j;

	i = -1;
	while (++i < pipes)
	{
		j = -1;
		while (++j < pipes - 1)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
		waitpid(pids[i], &status, 0);
	}
	free(pids);
	free(fds);
}

static void	initson(int p_count, pid_t *pids, t_fd *fds, int i)
{
	int	j;

	if (pids[i] == 0)
	{
		if (i != p_count - 1)
			dup2(fds[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(fds[i - 1].fd[0], STDIN_FILENO);
		j = -1;
		while (++j < p_count - 1 && pids[i] == 0)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
	}
}

static void	execveson(pid_t *pids, int i, t_pp *process)
{
	if (pids[i] == 0)
	{
		if (process->is_cmd == TRUE)
			execve(process->pathname, process->argv, NULL);
		else if (process->is_builtin == TRUE)
		{
			ft_builtins(process->argv);
			exit(g_var.last_cmd_status);
		}
	}
}

static void	run_multi_process(t_pp **processes, int p_count)
{
	int		i;
	pid_t	*pids;
	t_pp	*process;
	t_fd	*fds;

	process = *processes;
	pids = (pid_t *)malloc(sizeof(pid_t) * p_count);
	fds = (t_fd *)malloc(sizeof(t_fd) * p_count - 1);
	i = -1;
	while (++i < p_count - 1)
		pipe(fds[i].fd);
	i = -1;
	while (++i < p_count)
	{
		pids[i] = fork();
		initson(p_count, pids, fds, i);
		execveson(pids, i, process);
		process = process->next;
	}
	close_forkedpipes(p_count, pids, fds);
}

void	run_processes(t_pp **processes, int p_count)
{
	if (p_count != 0 && *processes != NULL)
	{
		if (p_count == 1 && processes[0]->is_builtin == TRUE)
			ft_builtins(processes[0]->argv);
		else
			run_multi_process(processes, p_count);
	}
}
