/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:42 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/31 21:33:26 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * * Close processes
 * @param p_count	number of processes to run
 * @param pid		father processes waiting for childs
 * @param fds		file descriptors to comunicate process
*/
static void	close_processes(int p_count, pid_t *pids, t_fd *fds)
{
	int		status;
	int		i;
	int		j;

	i = -1;
	while (++i < p_count)
	{
		j = -1;
		while (++j < p_count - 1)
		{
			close(fds[j].fd[READ_END]);
			close(fds[j].fd[WRITE_END]);
		}
		waitpid(pids[i], &status, 0);
	}
	if (WIFEXITED(status))
		g_var.current_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_var.current_status = WTERMSIG(status);
	free(pids);
	free(fds);
}

/**
 * * Init process
 * @param process	process to exec
 * @param p_count	number of processes to run
 * @param fds		file descriptors to comunicate process
 * @param id		id process to handle pipe conections
*/
static void	init_process(t_p *process, int p_count, t_fd *fds, int id)
{
	int		j;

	if (id != p_count - 1)
		dup2(fds[id].fd[WRITE_END], STDOUT_FILENO);
	if (id != 0)
		dup2(fds[id - 1].fd[READ_END], STDIN_FILENO);
	process_redirections(process->redir);
	j = -1;
	while (++j < p_count - 1)
	{
		close(fds[j].fd[READ_END]);
		close(fds[j].fd[WRITE_END]);
	}
}

/**
 * * Run process
 * @param process	process to exec
 * @param envp		environment array
*/
static void	run_process(t_p *process, char **envp)
{
	if (process->type == TEXT)
		exit(process->status);
	else if (process->type == BUILTIN)
	{
		ft_builtins(process->argv);
		exit(g_var.current_status);
	}
	else
		execve(process->pathname, process->argv, envp);
}

/**
 * * Create processes with retrieved info
 * @param processes	processes to run
 * @param p_count	number of processes to run
 * @param envp		environment array
*/
static void	create_processes(t_p *process, int p_count, char **envp)
{
	int		i;
	pid_t	*pids;
	t_fd	*fds;

	pids = (pid_t *)malloc(sizeof(pid_t) * p_count);
	fds = (t_fd *)malloc(sizeof(t_fd) * p_count - 1);
	i = -1;
	while (++i < p_count - 1)
		pipe(fds[i].fd);
	i = -1;
	while (++i < p_count)
	{
		pids[i] = fork();
		signal(SIGINT, &signal_handler_process_sigint);
		if (pids[i] == 0)
		{
			init_process(process, p_count, fds, i);
			run_process(process, envp);
		}
		process = process->next;
	}
	megafree(&envp);
	close_processes(p_count, pids, fds);
	exit(g_var.current_status);
}

/**
 * * Run processes
 * @param processes	processes to run
 * @param p_count	number of processes to run
*/
void	run_processes(t_p **processes, int p_count)
{
	pid_t	pid;
	int		status;

	if (p_count != 0 && *processes != NULL)
	{
		if (p_count == 1 && processes[0]->type == BUILTIN \
		&& processes[0]->redir == NULL)
		{
			process_redirections(processes[0]->redir);
			ft_builtins(processes[0]->argv);
		}
		else
		{
			pid = fork();
			signal_handler_forks(pid);
			if (pid == 0)
				create_processes(*processes, p_count, \
								lst_str_to_array(&g_var.env));
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_var.current_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_var.current_status = WTERMSIG(status);
		}
	}
}
