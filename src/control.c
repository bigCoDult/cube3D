/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:20:32 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:36:19 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	find_player_position(t_ray *ray)
{
	int		y;
	int		x;
	char	player_char;

	y = 0;
	player_char = '\0';
	while (y < ray->map_height)
	{
		x = 0;
		while (x < ray->map_width && ray->map_data[y][x])
		{
			if (ray->map_data[y][x] == 'N' || ray->map_data[y][x] == 'S' ||
				ray->map_data[y][x] == 'E' || ray->map_data[y][x] == 'W')
			{
				player_char = ray->map_data[y][x];
				ray->posx = x + 0.5;
				ray->posy = y + 0.5;
				return (player_char);
			}
			x++;
		}
		y++;
	}
	return ('\0');
}

void	set_player_direction(t_ray *ray, char player_char)
{
	if (player_char == 'N')
		set_north_direction(ray);
	else if (player_char == 'S')
		set_south_direction(ray);
	else if (player_char == 'E')
		set_east_direction(ray);
	else if (player_char == 'W')
		set_west_direction(ray);
	else
		set_default_player(ray);
}

void	init_player(t_ray *ray)
{
	char	player_char;

	player_char = find_player_position(ray);
	set_player_direction(ray, player_char);
}
