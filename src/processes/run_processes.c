/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:39:42 by emadriga          #+#    #+#             */
/*   Updated: 2022/01/25 12:51:27 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_fd{
	int	fd[2];
}t_fd;

static void	close_forkedpipes(int p_count, pid_t *pids, t_fd *fds)
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

static void	initson(t_p *process, int p_count, t_fd *fds, int i)
{
	int		j;

	if (i != p_count - 1)
		dup2(fds[i].fd[WRITE_END], STDOUT_FILENO);
	if (i != 0)
		dup2(fds[i - 1].fd[READ_END], STDIN_FILENO);
	process_redirections(process->redir);
	j = -1;
	while (++j < p_count - 1)
	{
		close(fds[j].fd[READ_END]);
		close(fds[j].fd[WRITE_END]);
	}
}

static void	execveson(t_p *process, char **envp)
{
	if (process->is_cmd == TRUE)
		execve(process->pathname, process->argv, envp);
	else if (process->is_builtin == TRUE)
	{
		ft_builtins(process->argv);
		exit(g_var.current_status);
	}
}

static void	run_multi_process(t_p *process, int p_count, char **envp)
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
		signal_handler_forks(pids[i]);
		if (pids[i] == 0)
		{
			initson(process, p_count, fds, i);
			execveson(process, envp);
		}
		process = process->next;
	}
	close_forkedpipes(p_count, pids, fds);
	signal_handler_default();
}

void	run_processes(t_p **processes, int p_count)
{
	char	**envp;

	envp = NULL;
	if (p_count != 0 && *processes != NULL)
	{
		if (p_count == 1 && processes[0]->is_builtin == TRUE)
			ft_builtins(processes[0]->argv);
		else
		{
			envp = lst_str_to_array(&g_var.env);
			run_multi_process(*processes, p_count, envp);
			megafree(&envp);
		}
	}
}
