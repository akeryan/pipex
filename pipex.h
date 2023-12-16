/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:03:49 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 11:33:08 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

typedef enum e_arg_type
{
	INT,
	PTR
}	t_arg_type;

char	*get_path(char *cmd, char *env[]);

//error managing
void	error_check(void *ptr, char *msg, t_arg_type type);
void	error_msg(char *msg);

# ifndef BONUS_AVAILABLE
#  define BONUS 0
# else 
#  define BONUS 1
# endif

#endif