/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:23 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/21 22:03:49 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_check(void *ptr, char *msg, t_arg_type type)
{
	if (type == PTR)
	{
		if (ptr == NULL)
			perror_msg(msg);
	}
	else if (type == INT)
	{
		if (*(int *)ptr < 0)
			perror_msg(msg);
	}
	else
		perror_msg("Flag is wrong");
	return ;
}

void	error_msg(char *msg)
{
	ft_printf(1, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void	perror_msg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
