/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:03:25 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/23 16:03:06 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	***read_args(char **args, int num);
static int	**get_pipes(int len);
static int	*get_pids(int len);

void	init(t_data *d, int argc, char **argv)
{
	d->proc_num = parsing(argc, argv);
	d->args = read_args(argv, d->proc_num);
	d->pids = get_pids(d->proc_num);
	d->pipes = get_pipes(d->proc_num - 1);
	d->pth = NULL;
	d->i = 0;
}

static char	***read_args(char **args, int num)
{
	char	***out;
	int		i;

	if (num <= 0)
		return (NULL);
	out = (char ***)malloc((num + 1) * sizeof(char **));
	error_check(out, "Error: malloc failed for split in read_args", PTR);
	i = -1;
	while (++i < num)
	{
		if (ft_strchr(args[i + 2], '\'') != NULL)
			out[i] = split_cmd(args[i + 2], '\'');
		else
			out[i] = ft_split(args[i + 2], ' ');
		if (out[i] == NULL)
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			ft_printf(2, "Error: malloc in read_args: %s", strerror(errno));
		}
	}
	out[num] = NULL;
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

	pipes = (int **)malloc((len + 1) * sizeof(int *));
	i = -1;
	while (++i < len)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			ft_printf(2, "Error: malloc in get_pipes(): %s\n", strerror(errno));
		}
	}
	pipes[len] = NULL;
	return (pipes);
}
