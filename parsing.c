/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:33:31 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/16 15:59:07 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parsing(int argc, char *argv[])
{
	if (BONUS == 0)
	{
		if (argc > 5)
			error_msg("Error: number of arguments is greater than 4");
	} else if (BONUS == 1)
	{

	}
	(void)argv;
	return ;
}