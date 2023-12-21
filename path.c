/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:56 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/21 15:14:29 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_path_indx(char *env[]);

char	*get_cmd_path(char *cmd, char *env[])
{
	char	**paths;
	char	*pth[2];
	int		loc;
	int		i;

	loc = get_path_indx(env);
	error_check(&loc, "No PATH: get_path_indx()", INT);
	paths = ft_split(env[loc], ':');
	error_check(paths, "Memory allocation failed in ft_split()", PTR);
	i = 0;
	while (paths[++i])
	{
		pth[0] = ft_strjoin(paths[i], "/");
		error_check(pth[0], "Mem alloc fail for strjoin in get_cmd_path", PTR);
		pth[1] = ft_strjoin(pth[0], cmd);
		error_check(pth[1], "Mem alloc fail for strjoin in get_cmd_path", PTR);
		free(pth[0]);
		if (access(pth[1], F_OK) == 0)
		{
			free_split(paths);
			return (pth[1]);
		}
		free(pth[1]);
	}
	return (free_split(paths), NULL);
}

static int	get_path_indx(char *env[])
{
	int	i;
	int	loc;

	i = 0;
	while (env[i])
	{
		loc = ft_strncmp(env[i], "PATH", 4);
		if (loc == 0)
			return (i);
		i++;
	}
	return (-1);
}
