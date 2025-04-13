/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:20:55 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:13:00 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// 텍스처 인덱스 결정 함수
int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0 && ray->rayDirX > 0)
		return (0);
	else if (ray->side == 0 && ray->rayDirX < 0)
		return (1);
	else if (ray->side == 1 && ray->rayDirY > 0)
		return (2);
	else
		return (3);
}
