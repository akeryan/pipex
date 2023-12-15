/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:23 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/15 20:52:08 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_ptr(void *ptr, char *f_name)
{
	if (ptr == NULL)
	{
		printf("Something wrong with %s\n", f_name);
		exit(EXIT_FAILURE);
	}
}

void	error_value(int v, char *f_name)
{
	if (v < 0)
	{
		printf("Something wrong with %s\n", f_name);
		exit(EXIT_FAILURE);
	}
}