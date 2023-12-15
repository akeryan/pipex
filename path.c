/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:44:56 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/15 20:01:58 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_path_indx(char *env[]);

char *get_path(char *cmd, char *env[])
{
	char **paths = ft_split(env[4], ':');
	while (paths[i] != NULL)
	{
		printf("%s\n", paths[i]);
		i++;
	}
	return ("Aram");
}

static int	get_path_indx(char *env[])
{
	int i = 0;
	int loc;

	while (env[i])
	{
		loc = ft_strncmp(env[i], "PATH", 4);
		if ( loc == 0)
			return (i);	
		i++;
	}
	return (-1);
}