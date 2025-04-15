/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:21:00 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 06:59:56 by yutsong          ###   ########.fr       */
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
	ray->screenx = x;
	ray->camerax = 2 * ray->screenx / (double)ray->screenwidth - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

// 메인 레이캐스팅 함수
void	raycast(t_total *total)
{
	int		width;
	t_ray	*ray;

	ray = (t_ray *)total->ray;
	width = 0;
	while (width < ray->screenwidth)
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
