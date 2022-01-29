#include "minishell.h"

void	command_sorter_no_pipes(t_red *red_node, char **env, int fdi, int fdo)
{
	int	frk;
	int	status;

	frk = 0;
	if (!ft_strcmp(red_node -> params[0], "echo"))
		ft_echo(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "exit"))
		ft_exit(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "export"))
		ft_export(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "pwd"))
		ft_pwd(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "unset"))
		ft_unset(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "env"))
		ft_env(red_node -> params);
	else if (!ft_strcmp(red_node -> params[0], "cd"))
		ft_cd(red_node -> params);
	else
	{
		frk = fork();
		if (env)
			write(1, "hi", 0);
		signal_handler_forks(!frk);
		if (!frk)
			execve(red_node -> path, red_node -> params, env);
		wait(&status);
		g_var.current_status = WEXITSTATUS(status);
		if (fdi != 0)
			close(fdi);
		if (fdo != 1)
			close(fdo);
	}
}

void	command_sorter_wth_pipes(t_red *red_node, char **env, int fdi)
{
	int	frk;

	frk = fork();
	signal_handler_forks(!frk);
	if (!frk)
	{
		close(fdi);
		if (!ft_strcmp(red_node -> params[0], "echo"))
			ft_echo(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "exit"))
			ft_exit(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "export"))
			ft_export(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "pwd"))
			ft_pwd(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "unset"))
			ft_unset(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "env"))
			ft_env(red_node -> params);
		else if (!ft_strcmp(red_node -> params[0], "cd"))
			ft_cd(red_node -> params);
		else
			exit(execve(red_node -> path, red_node -> params, env));
		exit (0);
	}
}
