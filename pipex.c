/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/20 16:01:16 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	d;

	init(&d, argc, argv);

	d.i = -1;	
	while (++d.i < d.proc_num - 1)
	{
		if (pipe(d.pipes[d.i]) == -1)
			perror_msg("Pipe failed: pipes");
		// if failed -> close created pipes...
	}

	int h = -1;	
	while (++h < d.proc_num)
	{
		d.pids[h] = fork();
		if (d.pids[h] == -1)
			perror_msg("Error: fork() failed in main");
		if (d.pids[h] == 0)
		{
			if (h == 0)
			{
				if (dup2(d.file_fd[h], STDIN_FILENO) == -1)
					perror_msg("dup2 failed");
			}
			else
			{
				if (dup2(d.pipes[h - 1][0], STDIN_FILENO) == -1)
					perror_msg("dup2 failed");
			}

			if (h == d.proc_num - 1)
			{	
				if (dup2(d.file_fd[h], STDOUT_FILENO) == -1)
					perror_msg("dup2 failed for file_fd[1]");
			}	
			else
			{
				if (dup2(d.pipes[h][1], STDOUT_FILENO) == -1)
					perror_msg("dup2 failed for pipes in main");
			}

			if (h == 1)
			{
				char txt[100];
				read(STDIN_FILENO, txt, 99);
			//	write(STDOUT_FILENO, txt, 99);
				printf("TXT FROM CHILD: %s\n", txt);
			}
			int k = -1;
			while (++k < d.proc_num - 1)
			{
				close(d.pipes[k][0]);
				close(d.pipes[k][1]);
			}
			close(d.file_fd[0]);
			close(d.file_fd[1]);

			d.pth = get_cmd_path(d.args[h][0], env);
			error_check(d.pth, "get_cmd_path() failed", PTR);
			if (execve(d.pth, d.args[h], env) == -1)
				perror_msg("execve failed");
			return (0);
		} 
	}
	int k = -1;
	while (++k < d.proc_num - 1)
	{
		printf("pipe[%d][0]: %d\n", k, d.pipes[k][0]);
		printf("pipe[%d][1]: %d\n", k, d.pipes[k][1]);
	}
	int j = -1;
	while (++j < d.proc_num)	
		waitpid(d.pids[j], NULL, 0);
	destroy(&d);
	return (0);
}