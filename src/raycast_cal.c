/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:20:50 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:00:45 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 광선의 방향과 시작 지점에서의 사이드 거리 계산
void	calculate_step(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - ray->posy) * ray->deltadisty;
	}
}

// 거리계산
void	cal_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist
			= (ray->mapx - ray->posx + (1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist
			= (ray->mapy - ray->posy + (1 - ray->stepy) / 2) / ray->raydiry;
}

// 벽 높이 및 텍스쳐 좌표 계산
void	cal_wall_height(t_ray *ray)
{
	ray->lineheight = (int)(ray->screenheight / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + ray->screenheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + ray->screenheight / 2;
	if (ray->drawend >= ray->screenheight)
		ray->drawend = ray->screenheight - 1;
}

// 벽 텍스처 계산 함수 추가
void	cal_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
		ray->wallx = ray->posy + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = ray->posx + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * 64.0);
	if ((ray->side == 0 && ray->raydirx > 0)
		|| (ray->side == 1 && ray->raydiry < 0))
		ray->texx = 64 - ray->texx - 1;
	ray->step = 1.0 * 64 / ray->lineheight;
	ray->texpos = (
			ray->drawstart - ray->screenheight
			/ 2 + ray->lineheight / 2) * ray->step;
}
