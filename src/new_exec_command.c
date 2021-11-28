#include "minishell.h"

static void	command_sorter_no_pipes(t_red *red_node, char **env, int fdi, int fdo)
{
	int	frk;
	int	status;

	frk = 0;
	if (!strcmp(red_node -> params[0], "echo"))
		ft_echo(red_node -> params);
	else if (!strcmp(red_node -> params[0], "export"))
		ft_export(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "pwd"))
		ft_pwd(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "unset"))
		ft_unset(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "env"))
		ft_env(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "cd"))
		ft_cd(&g_var.env, red_node -> params);
	else
	{
		frk = fork();
		if (!frk)
			execve(red_node -> path, red_node -> params, env);
		wait(&status);
		g_var.status_error = WEXITSTATUS(status);
		if (fdi)
			close(fdi);
		if (fdo)
			close(fdo);
	}
}

static void	command_sorter_wth_pipes(t_red *red_node, char **env)
{
	if (!strcmp(red_node -> params[0], "echo"))
		ft_echo(red_node -> params);
	else if (!strcmp(red_node -> params[0], "export"))
		ft_export(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "pwd"))
		ft_pwd(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "unset"))
		ft_unset(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "env"))
		ft_env(&g_var.env, red_node -> params);
	else if (!strcmp(red_node -> params[0], "cd"))
		ft_cd(&g_var.env, red_node -> params);
	else
		exit(execve(red_node -> path, red_node -> params, env));
	exit (0);
}

/*
TODO	Check whether the infile/outfile are valid files. \
TODO		Directories are not valid files (check stat function).
*/
void	new_exec_command(t_red *red_node, char **env, int bool_addexit)
{
	int		a;
	int		fdi;
	int		fdo;
	char	*no_qm;

	a = 0;
	fdi = 0;
	fdo = 0;
	dup2(red_node -> pip_in, 0);
	dup2(red_node -> pip_out, 1);
	while (red_node -> redirs[a])
	{
		no_qm = adv_qm_rem(red_node -> redirs[a + 1], 0);
		if (!ft_strcmp(red_node -> redirs[a], "<"))
		{
			if (fdi)
				close(fdi);
			fdi = open(no_qm, O_RDONLY, 0666);
			dup2(fdi, 0);
		}
		if (!ft_strcmp(red_node -> redirs[a], ">"))
		{
			if (fdo)
				close(fdo);
			fdo = open(no_qm, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(fdo, 1);
		}
		if (!ft_strcmp(red_node -> redirs[a], ">>"))
		{
			if (fdo)
				close(fdo);
			fdo = open(no_qm, O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(fdo, 1);
		}
		if (!ft_strcmp(red_node -> redirs[a], "<<"))
		{
			if (fdi)
				close(fdi);
			if (ft_strchr(red_node -> redirs[a + 1], '\'') || ft_strchr(red_node -> redirs[a + 1], '"'))
				ft_heredoc_qm(&fdi, no_qm);
			else
				ft_heredoc(&fdi, red_node -> redirs[a + 1]);
			dup2(fdi, 0);
		}
		free(no_qm);
		a += 2;
	}
	if (bool_addexit)
		command_sorter_wth_pipes(red_node, env);
	else
		command_sorter_no_pipes(red_node, env, fdi, fdo);
}
