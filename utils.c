/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:11:16 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/21 10:44:15 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void dup_infile(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	error_check(fd, "Error: open(infile)", INT);
	if (dup2(*fd, STDIN_FILENO) == -1)
		perror_msg("dup2 failed");
	close(*fd);
}

void dup_outfile(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	error_check(fd, "Error: open(infile)", INT);
	if (dup2(*fd, STDOUT_FILENO) == -1)
		perror_msg("dup2 failed");
	close(*fd);
}

void	close_pipes(int **pipes, int len)
{
	int j;

	j = -1;
	while (++j < len)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}