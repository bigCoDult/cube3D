#include "../inc/cub3d.h"

void extract_img(t_total *total)
{
	int width;
	int height;

	width = 64;
	height = 64;
	total->parsed->image_info = malloc(sizeof(t_image_info));
	total->parsed->image_info->north = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->north, &width, &height);
	total->parsed->image_info->south = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->south, &width, &height);
	total->parsed->image_info->west = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->west, &width, &height);
	total->parsed->image_info->east = mlx_xpm_file_to_image(total->mlx->mlx_ptr,total->parsed->extracted_str->east, &width, &height);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->north, 0, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->south, 64, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->west, 0, 64);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->east, 64, 64);
}