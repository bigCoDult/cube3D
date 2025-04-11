#include "../inc/cub3d.h"

// DDA
void	dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapY >= 0 && ray->mapY < ray->map_height
			&& ray->mapX >= 0 && ray->mapX < ray->map_width
			&& ray->map_data[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}
