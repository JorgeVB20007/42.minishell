#include "minishell.h"

void	command_sorter_no_pipes(t_red *red_node, char **env, int fdi, int fdo)
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
		if (env)
			write(1, "hi", 0);
		signal_handler_forks(!frk);
		if (!frk)
		{
			execve(red_node -> path, red_node -> params, env);
			exit(0);
		}
		wait(&status);
		g_var.last_cmd_status = WEXITSTATUS(status);
		if (fdi != 0)
			close(fdi);
		if (fdo != 1)
			close(fdo);
	}
}

void	command_sorter_wth_pipes(t_red *red_node, char **env)
{
	int	frk;

	frk = fork();
	signal_handler_forks(!frk);
	if (!frk)
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
}

/*
TODO	Investigate under what circumstances a command should fail when
TODO	an invalid file is given as a redirection and when should it continue.
!		This might be removed soon.
*/
/*void	new_exec_command(t_red *red_node, char **env, int bool_addexit)
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
			if (!access(no_qm, R_OK) && ft_is_directory(no_qm))
			{
				if (fdi)
					close(fdi);
				fdi = open(no_qm, O_RDONLY, 0666);
				dup2(fdi, 0);
			}
			else
				perror("Error:");
		}
		if (!ft_strcmp(red_node -> redirs[a], ">"))
		{
			if ((!access(no_qm, W_OK)  && ft_is_directory(no_qm)) || access(no_qm, F_OK))
			{
				if (fdo)
					close(fdo);
				fdo = open(no_qm, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				dup2(fdo, 1);
			}
			else
				perror("Error:");
		}
		if (!ft_strcmp(red_node -> redirs[a], ">>"))
		{
			if (!access(no_qm, R_OK) && ft_is_directory(no_qm))
			{
				if (fdo)
					close(fdo);
				fdo = open(no_qm, O_CREAT | O_WRONLY | O_APPEND, 0666);
				dup2(fdo, 1);
			}
			else
				perror("Error:");
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
		bool_addexit++;									// ? To avoid errors. This is temporary
		command_sorter_wth_pipes(red_node, env);
	else
		command_sorter_no_pipes(red_node, env, fdi, fdo);
}*/
