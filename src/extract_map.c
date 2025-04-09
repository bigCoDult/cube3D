/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:33:50 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/09 09:40:29 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_start(char *file, int i)
{
	while (file[i] != '\0')
		i++;
	i--;
	while (i > 0 && is_map_part(file[i]))
		i--;
	while (file[i] != '\n')
		i++;
	while (file[i] == '\n')
		i++;
	return (i);
}

static void	set_rowcol(char *file, int i, int *row, int *col)
{
	int	line_i;

	line_i = 0;
	*col = 1;
	while (file[i] != '\0')
	{
		if (file[i] == '\n' && file[i + 1] == '\n')
			return ;
		else if (file[i] == '\n')
		{
			(*col)++;
			line_i = 0;
		}
		else
		{
			line_i++;
			if (line_i > *row)
				*row = line_i;
		}
		i++;
	}
	return ;
}

static void	*malloc_map(t_total *total, int row, int col)
{
	total->parsed->map = (char **)malloc(sizeof(char *) * (col + 1));
	total->parsed->map[col] = NULL;
	if (!total->parsed->map)
		return (NULL);
	col--;
	while (col >= 0)
	{
		total->parsed->map[col] = (char *)malloc(sizeof(char) * (row + 1));
		if (!total->parsed->map[col])
			return (NULL);
		ft_memset(total->parsed->map[col], ' ', row);
		total->parsed->map[col][row] = '\0';
		col--;
	}
	return (total->parsed->map);
}

static void	do_rowcol_job(char *file, int *i, t_total *total)
{
	int	col;
	int	row;

	row = 0;
	col = 0;
	*i = find_map_start(file, *i);
	set_rowcol(file, *i, &row, &col);
	total->parsed->max = (t_cordi){col, row};
	malloc_map(total, row, col);
}

void	extract_map(char *file, t_total *total)
{
	int	i;
	int	col;
	int	row;

	i = 0;
	row = 0;
	col = 0;
	do_rowcol_job(file, &i, total);
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
		{
			col++;
			row = 0;
		}
		else
		{
			total->parsed->map[col][row] = file[i];
			if (file[i] != '1' && file[i] != '0' && file[i] != \
				' ' && file[i] != '\n' && file[i] != '\0')
				*(total->parsed->player) = (t_cordi){col, row};
			row++;
		}
		i++;
	}
}
