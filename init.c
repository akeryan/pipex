/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:03:25 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/18 11:48:36 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	*get_file_fds(char *file1, char *file2);
static char ***read_args(char *args[], int num);
static int	**get_pipes(int len);
static int	*get_pids(int len);

void	init(t_data *d, int argc, char *argv[])
{
	d->proc_num = parsing(argc, argv);
	d->args = read_args(argv, d->proc_num);
	d->pids = get_pids(d->proc_num);
	d->pipes = get_pipes(d->proc_num - 1);	
	d->file_fd = get_file_fds(argv[1], argv[argc - 1]);
	d->pth = NULL;
	d->i = 0;
}

static char ***read_args(char *args[], int num)
{
	char	***out;
	int		i;

	if (num <= 0)
		return (NULL);
	out = (char ***)malloc(num * sizeof(char **));
	error_check(out, "Error: malloc failed for split in read_args", PTR);
	i = -1;
	while (++i < num)
	{
		out[i] = ft_split(args[i + 2], ' ');
		if (out[i] == NULL)
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			error_msg("Error: malloc failed for split in read_args");
		}
	}
	return (out);
}

static int	*get_pids(int len)
{
	int	*pids;

	pids = (int *)malloc(len * sizeof(int));
	error_check(pids, "Error: malloc failed in get_pids()", PTR);
	return (pids);
}

static int	**get_pipes(int len)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(len * sizeof(int *));
	i = -1;
	while (++i < len)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			error_msg("Error: malloc failed in get_pipes()");
		}
	}
	return (pipes);
}

static int	*get_file_fds(char *file1, char *file2)
{
	int *file_fd;

	file_fd = (int *)malloc(2 * sizeof(int));
	file_fd[0] = open(file1, O_RDONLY);
	error_check(&file_fd[0], "File openning failed: file_fd[0]", INT);
	file_fd[1] = open(file2, O_RDWR | O_CREAT, 0664);
	error_check(&file_fd[1], "File openning failed: file_fd[1]", INT);
	return (file_fd);
}