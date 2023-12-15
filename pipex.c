/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/15 14:34:14 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	char	**args[2];
	int		pid[2]; // process id's
	int		pipe_fd[2]; // pipes
	char	*cmd[2];
	//pid_t	w_pid[2];
	//int		w_state[2];
	int		file_fd[2]; // files

	if (argc < 1) { perror("Number of arguments is incorrect\n"); return (1); }

	file_fd[0] = open(argv[1], O_RDONLY);
	//file_fd[1] = open(argv[4], O_RDWR | O_CREAT, 0664);
	if (file_fd[0] == -1) { perror("file 0 openning failed\n"); return (7); }
	//if (file_fd[1] == -1) { perror("file 1 openning failed\n"); return (7); }

	if(dup2(file_fd[0], STDIN_FILENO) == -1) { perror("dup2 in parent process failed\n"); return (6); }
	close(file_fd[0]);
	
	if (pipe(pipe_fd) == -1) { perror("pipe has broken\n"); return (2); }	

	args[0] = ft_split(argv[2], ' ');
	if (args[0] == NULL) {perror("memory allocation for args[0] failed"); return (1);}
	//args[1] = ft_split(argv[3], ' ');
	//if (args[1] == NULL) {perror("memory allocation for args[1] failed"); return (1);}

	//int i = 0;
	//printf("cmd_1: ");
	//while(args[0][i] != NULL)
	//{
		//printf("%s ", args[0][i]);
		//i++;
	//}
	//printf("\n");
	//printf("cmd_2: ");
	//i = 0;
	//while(args[1][i] != NULL)
	//{
		//printf("%s ", args[1][i]);
		//i++;
	//}
	//printf("\n");

	pid[0] = fork();
	if (pid[0] == -1) {printf("pid[0] = fork() failed\n"); return (1); }

	if (pid[0] == 0)
	{	//first child process
		//if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) { perror("dup2 in child process 1 failed\n"); return (4); }
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(file_fd[0]);
		char *path = "/bin/";
		cmd[0] = ft_strjoin(path, args[0][0]);
		if (execve(cmd[0], args[0], NULL) == -1)
			perror("execve broke, smth went wrong");
	}	
	
	return (0);
}