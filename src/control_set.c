/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:54:40 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:56:01 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 북쪽 방향 설정 함수
void	set_north_direction(t_ray *ray)
{
	ray->dirX = 0;
	ray->dirY = -1;
	ray->planeX = 0.66;
	ray->planeY = 0;
}

// 남쪽 방향 설정 함수
void	set_south_direction(t_ray *ray)
{
	ray->dirX = 0;
	ray->dirY = 1;
	ray->planeX = -0.66;
	ray->planeY = 0;
}

// 동쪽 방향 설정 함수
void	set_east_direction(t_ray *ray)
{
	ray->dirX = 1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
}

// 서쪽 방향 설정 함수
void	set_west_direction(t_ray *ray)
{
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = -0.66;
}

// 기본 값 설정 함수
void	set_default_player(t_ray *ray)
{
	ray->posX = 2;
	ray->posY = 2;
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
}
