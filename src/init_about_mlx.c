#include "../inc/cub3d.h"

int init_about_mlx(t_total *total)
{
	total->mlx = malloc(sizeof(t_mlx));
	total->mlx->mlx_ptr = mlx_init();
	total->mlx->win_ptr = mlx_new_window(total->mlx->mlx_ptr, 300, 300, "pokemon mountain");
	extract_img(total);
	
	
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->north, 0, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->south, 64, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->west, 0, 64);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->east, 64, 64);
	// mlx_loop_end(total->mlx->mlx_ptr);
	mlx_loop(total->mlx->mlx_ptr);
	return (1);
}