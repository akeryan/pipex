/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:33:53 by akeryan           #+#    #+#             */
/*   Updated: 2023/12/23 18:20:33 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*substr_trim(char *str, unsigned int start, size_t len);
static int	fcount_words(char const *str, char c);

char	**split_cmd(char *str, char c)
{
	t_split_vars	d;

	d.start = ft_strchr(str, c);
	d.end = ft_strrchr(str, c);
	if (d.start && d.end && d.start != d.end)
	{
		d.prog = substr_trim(str, d.start - str + 1, d.end - d.start - 1);
		d.first_part = substr_trim(str, 0, d.start - str);
		d.last_part = substr_trim(str, d.end - str + 1, ft_strlen(str));
		d.wnum_f = fcount_words(d.first_part, ' ');
		d.wnum_l = fcount_words(d.last_part, ' ');
		d.out = (char **)malloc((d.wnum_f + d.wnum_l + 2) * sizeof(char *));
		d.split_f = ft_split(d.first_part, ' ');
		d.split_l = ft_split(d.last_part, ' ');
		d.fill_pos = -1;
		while (d.split_f[++d.fill_pos])
			d.out[d.fill_pos] = d.split_f[d.fill_pos];
		d.out[d.fill_pos] = d.prog;
		d.i = -1;
		while (d.split_l[++d.i])
			d.out[++d.fill_pos] = d.split_l[d.i];
		return (d.out);
	}
	return (NULL);
}

static char	*substr_trim(char *str, unsigned int start, size_t len)
{
	char	*substr;
	char	*tmp;

	tmp = ft_substr(str, start, len);
	substr = ft_strtrim(tmp, " ");
	free(tmp);
	return (substr);
}

static int	fcount_words(char const *str, char c)
{
	if (c == 0)
		return (1);
	while (*str == c)
		str++;
	if (*str == '\0')
		return (0);
	while (*str && *str != c)
		str++;
	return (1 + fcount_words(str, c));
}
