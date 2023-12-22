/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:23 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/22 10:53:15 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_check(void *ptr, char *msg, t_arg_type type)
{
	if (type == PTR)
	{
		if (ptr == NULL)
		{
			ft_printf(2, "Error: %s: %s\n", msg, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (type == INT)
	{
		if (*(int *)ptr < 0)
		{
			ft_printf(2, "Error: %s: %s\n", msg, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_printf(2, "Error: Flag is wrong");
	return ;
}
