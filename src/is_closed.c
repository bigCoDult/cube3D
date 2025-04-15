/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:56:16 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 14:56:26 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_part(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == '\n' \
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	check_8way(t_total *total, int col, int row)
{
	if (col == 0 || row == 0 || col == total->parsed->max.col -1 \
		|| row == total->parsed->max.row - 1)
		return (0);
	if (total->parsed->map[col - 1][row] == ' ' || \
		total->parsed->map[col + 1][row] == ' ' \
	|| total->parsed->map[col][row - 1] == ' ' || \
	total->parsed->map[col][row + 1] == ' ' \
	|| total->parsed->map[col - 1][row - 1] == ' ' || \
	total->parsed->map[col - 1][row + 1] == ' ' \
	|| total->parsed->map[col + 1][row - 1] == ' ' \
	|| total->parsed->map[col + 1][row + 1] == ' ')
		return (0);
	return (1);
}

static int	is_inner_map(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_closed(t_total *total)
{
	t_cordi	cordi;

	cordi = (t_cordi){0, 0};
	while (total->parsed->map[cordi.col])
	{
		if (total->parsed->map[cordi.col][cordi.row] == '1' || \
			total->parsed->map[cordi.col][cordi.row] == ' ')
			cordi.row++;
		if (total->parsed->map[cordi.col][cordi.row] == '\0')
		{
			cordi.row = 0;
			cordi.col++;
			continue ;
		}
		if (is_inner_map(total->parsed->map[cordi.col][cordi.row]))
		{
			if (!check_8way(total, cordi.col, cordi.row))
				return (0);
			cordi.row++;
		}
	}
	return (1);
}
