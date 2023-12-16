/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:49 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 20:37:35 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

# ifndef BONUS_AVAILABLE
#  define BONUS 0
# else 
#  define BONUS 1
# endif

typedef enum e_arg_type
{
	INT,
	PTR
}	t_arg_type;

typedef struct	s_data
{
	char	**args[2];
	int		pids[2];
	int		pipes[2];
	int		file_fd[2];
	char	*pth;
} t_data;

void	parsing(int argc, char *argv[]);
char	*get_cmd_path(char *cmd, char *env[]);

//error managing
void	error_check(void *ptr, char *msg, t_arg_type type);
void	error_msg(char *msg);

#endif