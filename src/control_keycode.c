/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keycode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:25:03 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 09:26:14 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx + ray->dirx * movespeed)] != '1')
		ray->posx += ray->dirx * movespeed;
	if (ray->map_data
		[(int)(ray->posy + ray->diry * movespeed)][(int)(ray->posx)] != '1')
		ray->posy += ray->diry * movespeed;
}

void	move_backward(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx - ray->dirx * movespeed)] != '1')
		ray->posx -= ray->dirx * movespeed;
	if (ray->map_data
		[(int)(ray->posy - ray->diry * movespeed)][(int)(ray->posx)] != '1')
		ray->posy -= ray->diry * movespeed;
}

void	move_left(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx - ray->diry * movespeed)] != '1')
		ray->posx -= ray->diry * movespeed;
}

void	move_right(t_ray *ray, double movespeed)
{
	if (ray->map_data
		[(int)(ray->posy)][(int)(ray->posx + ray->diry * movespeed)] != '1')
		ray->posx += ray->diry * movespeed;
}
