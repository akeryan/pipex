/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 13:43:54 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	char	**args[2];
	int		pid[2];
	int		pipe_fd1[2];
	int		file_fd[2];
	char	*pth;

	parsing(argc, argv);

	if (argc < 1)
	error_msg("Number of arguments in main is incorrect");

	file_fd[0] = open(argv[1], O_RDONLY);
	error_check(&file_fd[0], "File openning failed: file_fd[0]", INT);
	file_fd[1] = open(argv[4], O_RDWR | O_CREAT, 0664);
	error_check(&file_fd[1], "File openning failed: file_fd[1]", INT);

	if (dup2(file_fd[0], STDIN_FILENO) == -1)
		error_msg("dup2 failed");
	close(file_fd[0]);
	
	if (pipe(pipe_fd1) == -1)
		error_msg("Pipe failed: pipe_fd1");

	args[0] = ft_split(argv[2], ' ');
	error_check(args[0], "Mem alloc failed for args[0]: split() in main", PTR);
	args[1] = ft_split(argv[3], ' ');
	error_check(args[1], "Mem alloc failed for args[1]: split() in main", PTR);

	pid[0] = fork();
	error_check(&pid[0], "fork failed for pid[0]: fork() in main", INT);

	if (pid[0] == 0)
	{	//first child process
		if (dup2(pipe_fd1[1], STDOUT_FILENO) == -1)
			error_msg("dup2 failed for pipe_fd1 in main");
		close(pipe_fd1[0]);
		close(pipe_fd1[1]);
		close(file_fd[0]);
		close(file_fd[1]);
		pth = get_cmd_path(args[0][0], env);
		if (execve(pth, args[0], env) == -1)
			error_msg("execve failed in child pid[0]");
		free(pth);
		pth = NULL;
	}	
	
	pid[1] = fork();
	error_check(&pid[1], "fork failed for pid[1]: fork() in main", INT);

	if (pid[1] == 0)
	{
		//second child process
		if (dup2(pipe_fd1[0], STDIN_FILENO) < 0)
			error_msg("dup2 failed for pipe_fd1[0]");
		if (dup2(file_fd[1], STDOUT_FILENO) < 0)
			error_msg("dup2 failed for file_fd[1]");
		close(pipe_fd1[0]);
		close(file_fd[1]);
		close(pipe_fd1[1]);
		close(file_fd[0]);
		pth = get_cmd_path(args[1][0], env);
		if (execve(pth, args[1], env) < 0)
			error_msg("execve failed in child pid[1]");
		free(pth);
		pth = NULL;
	}
}