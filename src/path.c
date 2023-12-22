/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:56 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/22 11:45:33 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*cmd_in_path(char *path, char **paths, char *cmd);
static int	get_path_indx(char **env);

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*pth;
	int		loc;
	int		i;

	if (cmd == NULL)
	{
		ft_printf(2, "Error: command is empty\n");
		exit(EXIT_FAILURE);
	}
	loc = get_path_indx(env);
	error_check(&loc, "No PATH: get_path_indx()", INT);
	paths = ft_split(env[loc], ':');
	error_check(paths, "Memory allocation failed in ft_split()", PTR);
	i = 0;
	while (paths[++i])
	{
		pth = cmd_in_path(paths[i], paths, cmd);
		if (pth)
			return (pth);
	}
	ft_printf(2, "Error: command not found: %s\n", cmd);
	free_split(paths);
	exit(EXIT_FAILURE);
}

static char	*cmd_in_path(char *path, char **paths, char *cmd)
{
	char	*pth[2];

	pth[0] = ft_strjoin(path, "/");
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
	return (NULL);
}

static int	get_path_indx(char **env)
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
