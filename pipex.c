/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/19 17:09:38 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	d;

	int my = open("my_file", O_RDWR | O_CREAT, 0664);
	(void)my;

	init(&d, argc, argv);

	d.i = -1;
	printf("proc_num: %d\n", d.proc_num);
	while (++d.i < d.proc_num)
	{	
		printf("arg(%d): %s\n", d.i, d.args[d.i][0]);
		d.pth = get_cmd_path(d.args[d.i][0], env);
		printf("(%d): path = %s\n", d.i, d.pth);
	}
	d.i = -1;	
	while (++d.i < d.proc_num - 1)
	{
		if (pipe(d.pipes[d.i]) == -1)
			perror_msg("Pipe failed: pipes");
		// if failed -> close created pipes...
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
				if (dup2(d.file_fd[0], STDIN_FILENO) == -1)
					perror_msg("dup2 failed");
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

			printf("Parent process printing\n");
			d.pth = get_cmd_path(d.args[d.i][0], env);
			printf("path from childe 1: %s\n", d.pth);
			printf("WOOHOOOO\n");
			printf("ARGS = %s\n", d.args[d.i][0]);

			//close(d.pipes[d.i][0]);
			//close(d.pipes[d.i][1]);
			//close(d.file_fd[0]);
			//close(d.file_fd[1]);


			if (execve(d.pth, d.args[d.i], env) == -1)
				perror_msg("execve failed");
			free(d.pth);
			d.pth = NULL;
			//wait(NULL);
			
			
			//if(d.i == 0)
			//{
				//char buf[20];
				//read(d.pipes[0][0], buf, 10);
				//write(my, buf, 10);

			//}
			//return (0);
		}
	}
	wait(NULL);
}