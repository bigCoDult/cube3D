/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:40:10 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:02:26 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 앞으로 이동하는 함수
void	move_forward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx + ray->dirx * movespeed)] != '1')
		ray->posx += ray->dirx * movespeed;
	if (ray->map_data
		[(int)(ray->posy + ray->diry * movespeed)][(int)(ray->posx)] != '1')
		ray->posy += ray->diry * movespeed;
}

// 뒤로 이동하는 함수
void	move_backward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx - ray->dirx * movespeed)] != '1')
		ray->posx -= ray->dirx * movespeed;
	if (ray->map_data
		[(int)(ray->posy - ray->diry * movespeed)][(int)(ray->posx)] != '1')
		ray->posy -= ray->diry * movespeed;
}

// 좌측으로 회전하는 함수
void	rotate_left(t_ray *ray, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirx;
	oldplanex = ray->planex;
	ray->dirx = ray->dirx * cos(-rotspeed) - ray->diry * sin(-rotspeed);
	ray->diry = olddirx * sin(-rotspeed) + ray->diry * cos(-rotspeed);
	ray->planex = ray->planex * cos(-rotspeed) - ray->planey * sin(-rotspeed);
	ray->planey = oldplanex * sin(-rotspeed) + ray->planey * cos(-rotspeed);
}

// 우측으로 회전하는 함수
void	rotate_right(t_ray *ray, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirx;
	oldplanex = ray->planex;
	ray->dirx = ray->dirx * cos(rotspeed) - ray->diry * sin(rotspeed);
	ray->diry = olddirx * sin(rotspeed) + ray->diry * cos(rotspeed);
	ray->planex = ray->planex * cos(rotspeed) - ray->planey * sin(rotspeed);
	ray->planey = oldplanex * sin(rotspeed) + ray->planey * cos(rotspeed);
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
