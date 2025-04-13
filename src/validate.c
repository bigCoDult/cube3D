/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:11:35 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/13 14:26:55 by sanbaek          ###   ########.fr       */
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

static int	is_closed(t_total *total)
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
		if (total->parsed->map[cordi.col][cordi.row] == '0' || \
			total->parsed->map[cordi.col][cordi.row] == 'N' \
		|| total->parsed->map[cordi.col][cordi.row] == 'S' || \
		total->parsed->map[cordi.col][cordi.row] == 'E' \
		|| total->parsed->map[cordi.col][cordi.row] == 'W')
		{
			if (!check_8way(total, cordi.col, cordi.row))
				return (0);
			cordi.row++;
		}
	}
	return (1);
}

static int	is_path(t_total *total)
{
	int	fd_north;
	int	fd_south;
	int	fd_east;
	int	fd_west;

	fd_north = open(total->parsed->extracted_str->north, O_RDONLY);
	fd_south = open(total->parsed->extracted_str->south, O_RDONLY);
	fd_east = open(total->parsed->extracted_str->east, O_RDONLY);
	fd_west = open(total->parsed->extracted_str->west, O_RDONLY);
	if (fd_north != -1)
		close(fd_north);
	if (fd_south != -1)
		close(fd_south);
	if (fd_east != -1)
		close(fd_east);
	if (fd_west != -1)
		close(fd_west);
	if (fd_north == -1 || fd_south == -1 || fd_east == -1 || fd_west == -1)
		return (0);
	else
		return (1);
}

int	is_xpm(t_total *total)
{
	if (ft_endwith(total->parsed->extracted_str->north, ".xpm") && \
		ft_endwith(total->parsed->extracted_str->south, ".xpm") && \
		ft_endwith(total->parsed->extracted_str->east, ".xpm") && \
		ft_endwith(total->parsed->extracted_str->west, ".xpm"))
		return (1);
	else
		return (0);
}

static int	is_on_keylist(char *file, int i)
{
	if (file[i] == '\0' || file[i + 1] == '\0')
		return (0);
	else if (file[i] == 'N' && file[i + 1] == 'O')
		return (2);
	else if (file[i] == 'S' && file[i + 1] == 'O')
		return (2);
	else if (file[i] == 'E' && file[i + 1] == 'A')
		return (2);
	else if (file[i] == 'W' && file[i + 1] == 'E')
		return (2);
	else if (file[i] == 'F' && file[i + 1] == ' ')
		return (1);
	else if (file[i] == 'C' && file[i + 1] == ' ')
		return (1);
	else
		return (0);
}

static int	skip_value(char *file, int i)
{
	if (file[i] != ' ')
		return (0);
	while ((file[i]) == ' ')
		i++;
	if (is_whitespace(file[i]))
		return (0);
	while (!is_whitespace(file[i]))
		i++;
	return (i);
}

int	is_no_trash(t_total *total)
{
	char	*file;
	int		i;
	int		map_start_i;
	int		skip;

	file = total->parsed->extracted_str->file;
	i = 0;
	map_start_i = find_map_start(file, 0);
	while (i < map_start_i)
	{
		while (is_whitespace(file[i]))
			i++;
		if (i >= map_start_i)
			break ;
		if (is_on_keylist(file, i))
			i += is_on_keylist(file, i);
		else
			return (0);
		skip = skip_value(file, i);
		if (skip)
			i = skip;
		else
			return (0);
	}
	return (1);
}

int	validate(t_total *total)
{
	if (is_closed(total) && is_path(total) && is_xpm(total) && is_no_trash(total))
		return (1);
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
