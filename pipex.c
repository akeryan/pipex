/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/17 13:57:22 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	d;

	parsing(argc, argv, &d);

	d.file_fd[0] = open(argv[1], O_RDONLY);
	error_check(&d.file_fd[0], "File openning failed: file_fd[0]", INT);
	d.file_fd[1] = open(argv[4], O_RDWR | O_CREAT, 0664);
	error_check(&d.file_fd[1], "File openning failed: file_fd[1]", INT);

	if (pipe(d.pipes) == -1)
		perror_msg("Pipe failed: pipes");

	d.args[0] = ft_split(argv[2], ' ');
	error_check(d.args[0], "Malloc failed for args[0]: split() in main", PTR);
	d.args[1] = ft_split(argv[3], ' ');
	error_check(d.args[1], "Malloc failed for args[1]: split() in main", PTR);

	d.pids[0] = fork();
	error_check(&d.pids[0], "fork failed for pids[0]: fork() in main", INT);
	d.pids[1] = fork();
	error_check(&d.pids[1], "fork failed for pids[1]: fork() in main", INT);

	if (d.pids[0] == 0)
	{	
		if (dup2(d.file_fd[0], STDIN_FILENO) == -1)
			perror_msg("dup2 failed");
		if (dup2(d.pipes[1], STDOUT_FILENO) == -1)
			perror_msg("dup2 failed for pipes in main");
		close(d.pipes[0]);
		close(d.pipes[1]);
		close(d.file_fd[0]);
		close(d.file_fd[1]);
		d.pth = get_cmd_path(d.args[0][0], env);
		if (execve(d.pth, d.args[0], env) == -1)
			perror_msg("execve failed in child pids[0]");
		free(d.pth);
		d.pth = NULL;
	}	

	if (d.pids[1] == 0)
	{
		if (dup2(d.pipes[0], STDIN_FILENO) < 0)
			perror_msg("dup2 failed for pipes[0]");
		if (dup2(d.file_fd[1], STDOUT_FILENO) < 0)
			perror_msg("dup2 failed for file_fd[1]");
		close(d.pipes[0]);
		close(d.pipes[1]);
		close(d.file_fd[0]);
		close(d.file_fd[1]);
		d.pth = get_cmd_path(d.args[1][0], env);
		if (execve(d.pth, d.args[1], env) < 0)
			perror_msg("execve failed in child pids[1]");
		free(d.pth);
		d.pth = NULL;
	}
}