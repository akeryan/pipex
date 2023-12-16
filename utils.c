/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:23 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 11:34:43 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_check(void *ptr, char *msg, t_arg_type type)
{
	if (type == PTR)
	{
		if (ptr == NULL)
			error_msg(msg);
	}
	else if (type == INT)
	{
		if (*(int *)ptr < 0)
			error_msg(msg);
	}
	else
	{
		error_msg("Flag is wrong");
	}
	return ;
}

void	error_msg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
