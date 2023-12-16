/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 20:43:14 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	a;

	parsing(argc, argv);

	a.file_fd[0] = open(argv[1], O_RDONLY);
	error_check(&a.file_fd[0], "File openning failed: file_fd[0]", INT);
	a.file_fd[1] = open(argv[4], O_RDWR | O_CREAT, 0664);
	error_check(&a.file_fd[1], "File openning failed: file_fd[1]", INT);

	if (pipe(a.pipes) == -1)
		error_msg("Pipe failed: pipes");

	a.args[0] = ft_split(argv[2], ' ');
	error_check(a.args[0], "Mem alloc failed for args[0]: split() in main", PTR);
	a.args[1] = ft_split(argv[3], ' ');
	error_check(a.args[1], "Mem alloc failed for args[1]: split() in main", PTR);

	a.pids[0] = fork();
	error_check(&a.pids[0], "fork failed for pids[0]: fork() in main", INT);
	a.pids[1] = fork();
	error_check(&a.pids[1], "fork failed for pids[1]: fork() in main", INT);

	if (a.pids[0] == 0)
	{	//first child process
		if (dup2(a.file_fd[0], STDIN_FILENO) == -1)
			error_msg("dup2 failed");
		if (dup2(a.pipes[1], STDOUT_FILENO) == -1)
			error_msg("dup2 failed for pipes in main");
		close(a.pipes[0]);
		close(a.pipes[1]);
		close(a.file_fd[0]);
		close(a.file_fd[1]);
		a.pth = get_cmd_path(a.args[0][0], env);
		if (execve(a.pth, a.args[0], env) == -1)
			error_msg("execve failed in child pids[0]");
		free(a.pth);
		a.pth = NULL;
	}	

	if (a.pids[1] == 0)
	{
		//second child process
		if (dup2(a.pipes[0], STDIN_FILENO) < 0)
			error_msg("dup2 failed for pipes[0]");
		if (dup2(a.file_fd[1], STDOUT_FILENO) < 0)
			error_msg("dup2 failed for file_fd[1]");
		close(a.pipes[0]);
		close(a.pipes[1]);
		close(a.file_fd[0]);
		close(a.file_fd[1]);
		a.pth = get_cmd_path(a.args[1][0], env);
		if (execve(a.pth, a.args[1], env) < 0)
			error_msg("execve failed in child pids[1]");
		free(a.pth);
		a.pth = NULL;
	}
}