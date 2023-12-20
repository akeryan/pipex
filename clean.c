/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:30:46 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/20 16:00:32 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void clean_args(char ***args);
static void	clean_pipes(int **p);

void destroy(t_data *d)
{
	clean_args(d->args);
	d->args = NULL;
	free(d->pids);
	clean_pipes(d->pipes);
	free(d->file_fd);
}

static void clean_args(char ***args)
{
	int	k;

	k = -1;
	while (args[++k])
		free_split(args[k]);
	free(args);
}

static void	clean_pipes(int **p)
{
	int k;

	k = -1;
	while (p[k])
		free(p[k]);
	free(p);
}

