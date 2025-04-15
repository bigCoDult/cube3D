/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:54:40 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:36:09 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_north_direction(t_ray *ray)
{
	ray->dirx = 0;
	ray->diry = -1;
	ray->planex = 0.66;
	ray->planey = 0;
}

void	set_south_direction(t_ray *ray)
{
	ray->dirx = 0;
	ray->diry = 1;
	ray->planex = -0.66;
	ray->planey = 0;
}

void	set_east_direction(t_ray *ray)
{
	ray->dirx = 1;
	ray->diry = 0;
	ray->planex = 0;
	ray->planey = 0.66;
}

void	set_west_direction(t_ray *ray)
{
	ray->dirx = -1;
	ray->diry = 0;
	ray->planex = 0;
	ray->planey = -0.66;
}

void	set_default_player(t_ray *ray)
{
	ray->posx = 2;
	ray->posy = 2;
	ray->dirx = -1;
	ray->diry = 0;
	ray->planex = 0;
	ray->planey = 0.66;
}
