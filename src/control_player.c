/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:40:10 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:43:28 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 앞으로 이동하는 함수
void	move_forward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posY)][(int)(ray->posX + ray->dirX * movespeed)] != '1')
		ray->posX += ray->dirX * movespeed;
	if (ray->map_data
		[(int)(ray->posY + ray->dirY * movespeed)][(int)(ray->posX)] != '1')
		ray->posY += ray->dirY * movespeed;
}

// 뒤로 이동하는 함수
void	move_backward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posY)][(int)(ray->posX - ray->dirX * movespeed)] != '1')
		ray->posX -= ray->dirX * movespeed;
	if (ray->map_data
		[(int)(ray->posY - ray->dirY * movespeed)][(int)(ray->posX)] != '1')
		ray->posY -= ray->dirY * movespeed;
}

// 좌측으로 회전하는 함수
void	rotate_left(t_ray *ray, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(-rotspeed) - ray->dirY * sin(-rotspeed);
	ray->dirY = olddirx * sin(-rotspeed) + ray->dirY * cos(-rotspeed);
	ray->planeX = ray->planeX * cos(-rotspeed) - ray->planeY * sin(-rotspeed);
	ray->planeY = oldplanex * sin(-rotspeed) + ray->planeY * cos(-rotspeed);
}

// 우측으로 회전하는 함수
void	rotate_right(t_ray *ray, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(rotspeed) - ray->dirY * sin(rotspeed);
	ray->dirY = olddirx * sin(rotspeed) + ray->dirY * cos(rotspeed);
	ray->planeX = ray->planeX * cos(rotspeed) - ray->planeY * sin(rotspeed);
	ray->planeY = oldplanex * sin(rotspeed) + ray->planeY * cos(rotspeed);
}

// 키 이벤트 처리 함수
int	key_press(int keycode, t_total *total)
{
	double	movespeed;
	double	rotspeed;
	t_ray	*ray;

	ray = (t_ray *)total->ray;
	movespeed = 0.05;
	rotspeed = 0.03;
	if (keycode == 53 || keycode == 65307)
		mlx_loop_end(total->mlx->mlx_ptr);
	else if (keycode == 3768 || keycode == 126 || keycode == 119)
		move_forward(ray, movespeed);
	else if (keycode == 3748 || keycode == 125 || keycode == 115)
		move_backward(ray, movespeed);
	else if (keycode == 3761 || keycode == 123 || keycode == 97)
		rotate_left(ray, rotspeed);
	else if (keycode == 3767 || keycode == 124 || keycode == 100)
		rotate_right(ray, rotspeed);
	raycast(total);
	return (0);
}
