/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:12:51 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:37:27 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ceiling(t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->drawstart)
	{
		ray->data[y * ray->screenwidth + x] = ray->ceiling_color;
		y++;
	}
}

void	draw_floor(t_ray *ray, int x)
{
	int	y;

	y = ray->drawend;
	while (y < ray->screenheight)
	{
		ray->data[y * ray->screenwidth + x] = ray->floor_color;
		y++;
	}
}

void	draw_wall_texture(t_ray *ray, int x, int tex_idx)
{
	int	y;
	int	color;
	int	tex_x;
	int	tex_y;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		tex_y = (int)ray->texpos & (ray->tex_height - 1);
		ray->texpos += ray->step;
		tex_x = ray->texx;
		color = ray->textures[tex_idx][tex_y * ray->tex_width + tex_x];
		ray->data[y * ray->screenwidth + x] = color;
		y++;
	}
}

void	draw_wall(t_ray *ray, int x)
{
	int	tex_idx;

	tex_idx = get_texture_index(ray);
	draw_ceiling(ray, x);
	draw_wall_texture(ray, x, tex_idx);
	draw_floor(ray, x);
}
