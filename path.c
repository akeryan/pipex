/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:56 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 11:39:29 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_path_indx(char *env[]);

char	*get_path(char *cmd, char *env[])
{
	char	**paths;
	char	*_pth;
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
		_pth = ft_strjoin(paths[i], "/");
		pth = ft_strjoin(_pth, cmd);
		if (access(pth, F_OK) == 0)
		{
			free(_pth);
			return (pth);
		}
		free(pth);
		free(_pth);
	}
	return (NULL);
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