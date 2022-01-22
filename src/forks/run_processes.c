/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:42 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/22 16:40:35 by emadriga         ###   ########.fr       */
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
			if (!ft_strcmp(process->argv[0], "echo"))
				ft_echo(&process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "exit"))
				ft_exit(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "export"))
				ft_export(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "pwd"))
				ft_pwd(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "unset"))
				ft_unset(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "env"))
				ft_env(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "cd"))
				ft_cd(&g_var.env, &process->argv[0]);
			else if (!ft_strcmp(process->argv[0], "exit"))
				ft_cd(&g_var.env, &process->argv[0]);
			exit(g_var.last_cmd_status);
		}
	}
}

void	create_forkedpipes(t_pp **processes, int pipes)
{
	int		i;
	pid_t	*pids;
	t_pp	*process;
	t_fd	*fds;

	process = *processes;
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
		execveson(pids, i, process);
		process = process->next;
	}
	close_forkedpipes(pipes, pids, fds);
}
