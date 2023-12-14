/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:27 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/14 19:37:34 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	char	**args[2];
	int		pid[2];
	int		pipe_fd[2];
	char	*cmd[2];
	pid_t	w_pid[2];
	int		w_state[2];
	int		file_fd[2];

	if (argc != 5) { perror("Number of arguments is incorrect\n"); return (0); }
	file_fd[0] = open(argv[1], O_RDONLY);
	file_fd[1] = open(argv[4], O_RDWR | O_CREAT, 0664);
	if (file_fd[0] == -1) { perror("file openning failed\n"); return (7); }
	if(dup2(file_fd[0], STDIN_FILENO) == -1) { perror("dup2 in parent process failed\n"); return (6); }
	close(file_fd[0]);
	if (pipe(pipe_fd) == -1) { perror("pipe has broke\n"); return (2); }	
	args[0] = ft_split(argv[2], ' ');
	args[1] = ft_split(argv[3], ' ');
	int i = 0;
	while(args[1][i] != NULL)
	{
		printf("%s\n", args[1][i]);
		i++;
	}
	pid[0] = fork();
	if (pid[0] == -1) {printf("pid[0] = fork() failed\n"); return (1); }
	if (pid[0] == 0)
	{	//first child process
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) { perror("dup2 in child process 1 failed\n"); return (4); }
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(file_fd[0]);
		cmd[0] = ft_strjoin("/usr/bin/", args[0][0]);
		if (execve(cmd[0], args[0], NULL) == -1)
			perror("execve broke, smth went wrong\n");
	}	
	
	pid[1] = fork();
	if (pid[0] < 0)
		return (3); 
	if (pid[1] == 0)
	{	//second child process
		if(dup2(pipe_fd[0], STDIN_FILENO) == -1) { perror("dup2 in child process 2 failed\n"); return (5); }	
		if(dup2(file_fd[1], STDOUT_FILENO) == -1) { perror("dup2 in child process 2 failed\n"); return (5); }	
		if(close(pipe_fd[0]) == -1) { perror("close fd[0] failed in child 2\n"); return (9);}
		if(close(pipe_fd[1]) == -1) { perror("close fd[1] failed in child 2\n"); return (10);}	
		cmd[1] = ft_strjoin("/usr/bin/", args[1][0]);
		if(cmd[1] == NULL) {perror("ft_strjoin returned NULL in child 2\n"); return (11);}
		if (execve(cmd[1], args[1], NULL) == -1)
			perror("execve broke, smth went wrong\n");
		perror("something went wrong in child process 2\n");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	w_pid[0] = waitpid(pid[0], &w_state[0], 0);
	//if (w_pid[0] > 0)
	//{
		//if(WIFEXITED(w_state[0] != 1)) 
			//perror("somethig wrong with child process 1");
		//if(WIFSIGNALED(w_state[0]))
			//perror("Child process 1 exited with signal");
    //} else if (w_pid[0] < 0)
	//{
		//perror("waitpid() 2");
		//return (8);
	//}
	w_pid[1] = waitpid(pid[1], &w_state[1], 0);
	//if (w_pid[1] > 0)
	//{
		//if(WIFEXITED(w_state[1] != 1)) 
			//perror("something wrong with child process 2");
		//if(WIFSIGNALED(w_state[1]))
			//perror("Child process 2 exited with signal");
    //} else if (w_pid[1] < 0)
	//{
		//perror("waitpid() 2");
		//return (8);
	//}	
	return (0);
}