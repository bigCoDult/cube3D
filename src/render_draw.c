/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:12:51 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:13:11 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 천장 그리기 함수
void	draw_ceiling(t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->drawStart)
	{
		ray->data[y * ray->screenWidth + x] = ray->ceiling_color;
		y++;
	}
}

// 바닥 그리기 함수
void	draw_floor(t_ray *ray, int x)
{
	int	y;

	y = ray->drawEnd;
	while (y < ray->screenHeight)
	{
		ray->data[y * ray->screenWidth + x] = ray->floor_color;
		y++;
	}
}

// 벽 텍스처 그리기 함수
void	draw_wall_texture(t_ray *ray, int x, int tex_idx)
{
	int	y;
	int	color;
	int	tex_x;
	int	tex_y;

	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		tex_y = (int)ray->texPos & (ray->tex_height - 1);
		ray->texPos += ray->step;
		tex_x = ray->texX;
		color = ray->textures[tex_idx][tex_y * ray->tex_width + tex_x];
		ray->data[y * ray->screenWidth + x] = color;
		y++;
	}
}

// 메인 벽 그리기 함수
void	draw_wall(t_ray *ray, int x)
{
	int	tex_idx;

	tex_idx = get_texture_index(ray);
	draw_ceiling(ray, x);
	draw_wall_texture(ray, x, tex_idx);
	draw_floor(ray, x);
}
