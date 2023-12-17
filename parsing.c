/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:33:31 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/17 15:27:11 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	check_quote_num(char *args[]);

int	parsing(int argc, char *argv[])
{
	if (BONUS == 0)
	{
		if (argc != 5)
			error_msg("Error: number of arguments is incorrect");
		return (2);
	}
	else if (BONUS == 1)
	{
		if (argc < 5)
			error_msg("Error: number of arguments is incorrect");
		return (argc - 3);
	}
	(void)argv;
}

//static void	check_quote_num(char *args[])
//{
	//int	num;
	//int	i;
	//int	j;

	//i = 0;
	//num = 0;
	//while (args[++i])
	//{
		//j = -1;
		//while (args[i][++j])
			//if (args[i][j] == '"')
				//num++;
	//}
	//if (num % 2 != 0)
		//error_msg("Error: there is an unclosed quote");
//}