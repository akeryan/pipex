/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:11:16 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/22 11:08:59 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	dup_infile(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		ft_printf(2, "Error: open failed: %s: %s\n", strerror(errno), file);
		exit(EXIT_FAILURE);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
		ft_printf(2, "Error: dup2 in dup_infile: %s\n", strerror(errno));
	close(*fd);
}

void	dup_outfile(int *fd, char *file)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*fd == -1)
	{
		ft_printf(2, "Error: open failed: %s: %s\n", strerror(errno), file);
		exit(EXIT_FAILURE);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
		ft_printf(2, "Error: dup2 in dup_outfile: %s\n", strerror(errno));
	close(*fd);
}

void	close_pipes(int **pipes, int len)
{
	int	j;

	j = -1;
	while (++j < len)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}
