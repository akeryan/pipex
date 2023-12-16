/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:56 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 12:42:54 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_path_indx(char *env[]);

char	*get_cmd_path(char *cmd, char *env[])
{
	char	**paths;
	char	*tmp;
	char	*pth;
	int		loc;
	int		i;

	loc = get_path_indx(env);
	error_check(&loc, "No PATH: get_path_indx()", INT);
	paths = ft_split(env[loc], ':');
	error_check(paths, "Memory allocation failed in ft_split()", PTR);
	i = 0;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		error_check(tmp, "Mem alloc failed for strjoin in get_cmd_path", PTR);
		pth = ft_strjoin(tmp, cmd);
		error_check(pth, "Mem alloc failed for strjoin in get_cmd_path", PTR);
		free(tmp);
		if (access(pth, F_OK) == 0)
		{
			free_split(paths);
			return (pth);
		}
		free(pth);
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