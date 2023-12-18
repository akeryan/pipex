/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/18 11:35:13 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	d;

	int my = open("my_file", O_RDWR | O_CREAT, 0664);

	init(&d, argc, argv);

	d.i = -1;
	printf("proc_num: %d\n", d.proc_num);
	while (++d.i < d.proc_num)
	{	
		printf("arg(%d): %s\n", d.i, d.args[d.i][0]);
		d.pth = get_cmd_path(d.args[d.i][0], env);
		printf("(%d): path = %s\n", d.i, d.pth);
	}
	d.i = 0;	
	while (d.i < d.proc_num - 1)
	{
		if (pipe(d.pipes[d.i]) == -1)
			perror_msg("Pipe failed: pipes");
		// if failed -> close created pipes...
		d.i++;
	}

	d.i = -1;
	while (++d.i < d.proc_num)
	{
		d.pids[d.i] = fork();
		if (d.pids[d.i] == -1)
			perror_msg("Error: fork() failed in main");
		if (d.pids[d.i] == 0)
		{
			printf("getpid(%d) from child: %d\n", d.i, getpid());

			if (d.i == 0)
			{
				char p[20] = "The sun is shining";
				if (read(d.file_fd[0], p, 5) == -1)
					perror_msg("Error: read failed");
				printf("Read from file: %s\n", p);

				if (dup2(d.file_fd[0], STDIN_FILENO) == -1)
					perror_msg("dup2 failed");
				printf("file_fd(%d) = %d\n", d.i, d.file_fd[0]);
				//if (write(my, p, 5) == -1)
					//perror_msg("Error: write failed");
			}
			else
			{
				if (dup2(d.pipes[d.i - 1][0], STDIN_FILENO) == -1)
					perror_msg("dup2 failed");
			}

			if (d.i == d.proc_num - 1)
			{	
				if (dup2(d.file_fd[1], STDOUT_FILENO) < 0)
					perror_msg("dup2 failed for file_fd[1]");
			}	
			else
			{
				if (dup2(d.pipes[d.i][1], STDOUT_FILENO) == -1)
					perror_msg("dup2 failed for pipes in main");
			}
			close(d.pipes[d.i][0]);
			close(d.pipes[d.i][1]);
			close(d.file_fd[0]);
			close(d.file_fd[1]);

			d.pth = get_cmd_path(d.args[d.i][0], env);
			write(my, d.pth, ft_strlen(d.pth));	

			if (execve(d.pth, d.args[d.i], env) == -1)
				perror_msg("execve failed");
			free(d.pth);
			d.pth = NULL;
			return (0);
		}
	}
	wait(NULL);
}