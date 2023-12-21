/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:33:31 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/21 19:18:00 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	parsing(int argc, char *argv[])
{
	if (BONUS == 0)
	{
		if (argc != 5)
			error_msg("Error: number of arguments is incorrect");
		return (argc - 3);
	}
	else if (BONUS == 1)
	{
		if (argc < 5)
			error_msg("Error: number of arguments is incorrect");
		return (argc - 3);
	}
	(void)argv;
}
