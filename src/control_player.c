/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:40:10 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 09:25:14 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		move_right(ray, movespeed);
	else if (keycode == 3767 || keycode == 124 || keycode == 100)
		move_left(ray, movespeed);
	else if (keycode == 3763 || keycode == 113 || keycode == 65361)
		rotate_left(ray, rotspeed);
	else if (keycode == 3764 || keycode == 101 || keycode == 65363)
		rotate_right(ray, rotspeed);
	raycast(total);
	return (0);
}
