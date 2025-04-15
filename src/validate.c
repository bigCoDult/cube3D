/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:11:35 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 14:57:45 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	is_color_range(char **color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!is_int_str(color[i]))
			return (0);
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	is_color(t_total *total)
{
	char	**ceiling;
	char	**floor;
	int		result;
	int		i;

	ceiling = ft_split(total->parsed->extracted_str->ceiling, ',');
	floor = ft_split(total->parsed->extracted_str->floor, ',');
	if (ceiling == NULL || floor == NULL)
		return (0);
	if (is_color_range(ceiling) && is_color_range(floor))
		result = 1;
	else
		result = 0;
	i = 0;
	while (ceiling[i])
		free(ceiling[i++]);
	i = 0;
	while (floor[i])
		free(floor[i++]);
	free(ceiling);
	free(floor);
	return (result);
}

int	validate(t_total *total)
{
	if (is_closed(total) && is_path(total) && is_xpm(total) \
	&& is_no_trash(total) && is_color(total))
		return (1);
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
