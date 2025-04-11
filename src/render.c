#include "../inc/cub3d.h"

void	init_image(t_total *total, t_ray *ray)
{
	ray->screenWidth = 800;
	ray->screenHeight = 600;
	ray->img = mlx_new_image(
			total->mlx->mlx_ptr, ray->screenWidth, ray->screenHeight);
	ray->data = (int *)mlx_get_data_addr(
			ray->img, &ray->bpp, &ray->size_line, &ray->endian);
}

// 텍스처 로드 함수
void	load_textures(t_total *total, t_ray *ray)
{
	int	width;
	int	height;

	ray->textures = tracked_malloc(total, sizeof(int *) * 4, "textures");
	ray->tex_imgs = tracked_malloc(total, sizeof(void *) * 4, "tex_imgs");
	ray->tex_imgs[0] = mlx_xpm_file_to_image(total->mlx->mlx_ptr,
			total->parsed->extracted_str->north, &width, &height);
	ray->textures[0] = (int *)mlx_get_data_addr(ray->tex_imgs[0],
			&ray->bpp, &ray->size_line, &ray->endian);
	ray->tex_imgs[1] = mlx_xpm_file_to_image(total->mlx->mlx_ptr,
			total->parsed->extracted_str->south, &width, &height);
	ray->textures[1] = (int *)mlx_get_data_addr(ray->tex_imgs[1],
			&ray->bpp, &ray->size_line, &ray->endian);
	ray->tex_imgs[2] = mlx_xpm_file_to_image(total->mlx->mlx_ptr,
			total->parsed->extracted_str->west, &width, &height);
	ray->textures[2] = (int *)mlx_get_data_addr(ray->tex_imgs[2],
			&ray->bpp, &ray->size_line, &ray->endian);
	ray->tex_imgs[3] = mlx_xpm_file_to_image(total->mlx->mlx_ptr,
			total->parsed->extracted_str->east, &width, &height);
	ray->textures[3] = (int *)mlx_get_data_addr(ray->tex_imgs[3],
			&ray->bpp, &ray->size_line, &ray->endian);
	ray->tex_width = width;
	ray->tex_height = height;
	ray->ceiling_color = ft_atohex(total->parsed->image_info->ceiling);
	ray->floor_color = ft_atohex(total->parsed->image_info->floor);
}

// 벽 그리기 함수
void	draw_wall(t_ray *ray, int x)
{
	int	y;
	int	color;
	int	tex_idx;
	int	tex_x;
	int	tex_y;

	if (ray->side == 0 && ray->rayDirX > 0)
		tex_idx = 0;
	else if (ray->side == 0 && ray->rayDirX < 0)
		tex_idx = 1;
	else if (ray->side == 1 && ray->rayDirY > 0)
		tex_idx = 2;
	else
		tex_idx = 3;
	y = 0;
	while (y < ray->drawStart)
	{
		ray->data[y * ray->screenWidth + x] = ray->ceiling_color;
		y++;
	}
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		ray->texY = (int)ray->texPos & (ray->tex_height - 1);
		ray->texPos += ray->step;
		tex_x = ray->texX;
		tex_y = ray->texY;
		color = ray->textures[tex_idx][tex_y * ray->tex_width + tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		ray->data[y * ray->screenWidth + x] = color;
		y++;
	}
	while (y < ray->screenHeight)
	{
		ray->data[y * ray->screenWidth + x] = ray->floor_color;
		y++;
	}
}
