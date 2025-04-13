/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:21:00 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:57:13 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 더미 맵 생성
void	create_dummy_map(t_total *total, t_ray *ray)
{
	int	col;

	col = 0;
	ray->map_data = total->parsed->map;
	ray->map_width = 0;
	while (total->parsed->map[col] != NULL)
	{
		if (ray->map_width < (int)ft_strlen(total->parsed->map[col]))
			ray->map_width = (int)ft_strlen(total->parsed->map[col]);
		col++;
	}
	ray->map_height = col;
}

// 광선 초기화
void	init_ray(t_total *total, t_ray *ray, int x)
{
	(void)total;
	ray->screenX = x;
	ray->cameraX = 2 * ray->screenX / (double)ray->screenWidth - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = (int)ray->posX;
	ray->mapY = (int)ray->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

// 메인 레이캐스팅 함수
void	raycast(t_total *total)
{
	int		width;
	t_ray	*ray;

	ray = (t_ray *)total->ray;
	width = 0;
	while (width < ray->screenWidth)
	{
		init_ray(total, ray, width);
		calculate_step(ray);
		dda(ray);
		cal_distance(ray);
		cal_wall_height(ray);
		cal_wall_texture(ray);
		draw_wall(ray, width);
		width++;
	}
	mlx_put_image_to_window(
		total->mlx->mlx_ptr, total->mlx->win_ptr, ray->img, 0, 0);
}

// 레이캐스팅 시작 함수
void	start_raycast(t_total *total)
{
	t_ray	*ray;

	total->ray = tracked_malloc(total, sizeof(t_ray), "ray");
	ray = (t_ray *)total->ray;
	create_dummy_map(total, ray);
	init_image(total, ray);
	init_player(ray);
	load_textures(total, ray);
	mlx_hook(total->mlx->win_ptr, 2, 1L << 0, key_press, total);
	mlx_hook(total->mlx->win_ptr, 17, 0, close_window, total);
	mlx_loop_hook(total->mlx->mlx_ptr, game_loop, total);
	raycast(total);
}
