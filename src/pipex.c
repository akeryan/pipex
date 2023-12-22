/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/22 10:25:09 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	execve_cmd(t_data *d, int argc, char **argv, char **env);

void	pipex(t_data *d, int argc, char **argv, char **env)
{
	d->i = -1;
	while (++d->i < d->proc_num - 1)
	{
		if (pipe(d->pipes[d->i]) == -1)
			ft_printf(2, "Error: pipe failed: %s\n", strerror(errno));
	}
	d->i = -1;
	while (++d->i < d->proc_num)
		execve_cmd(d, argc, argv, env);
	close_pipes(d->pipes, d->proc_num - 1);
	close(d->infile);
	close(d->outfile);
	d->i = -1;
	while (++d->i < d->proc_num)
		waitpid(d->pids[d->i], NULL, 0);
}

static void	execve_cmd(t_data *d, int argc, char **argv, char **env)
{
	d->pids[d->i] = fork();
	if (d->pids[d->i] == -1)
		ft_printf(2, "Error: fork() failed in main: %s\n", strerror(errno));
	if (d->pids[d->i] == 0)
	{
		if (d->i == 0)
			dup_infile(&d->infile, argv[1]);
		else
			if (dup2(d->pipes[d->i - 1][0], STDIN_FILENO) == -1)
				ft_printf(2, "Error: dup2 in execve_cmd: %s\n", strerror(errno));
		if (d->i == d->proc_num - 1)
			dup_outfile(&d->infile, argv[argc - 1]);
		else
			if (dup2(d->pipes[d->i][1], STDOUT_FILENO) == -1)
				ft_printf(2, "Error: dup2 in execve_cmd: %s\n", strerror(errno));
		close_pipes(d->pipes, d->proc_num - 1);
		d->pth = get_cmd_path(d->args[d->i][0], env);
		error_check(d->pth, "get_cmd_path() failed", PTR);
		execve(d->pth, d->args[d->i], env);
		ft_printf(2, "Error: execve in execve_cmd: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
