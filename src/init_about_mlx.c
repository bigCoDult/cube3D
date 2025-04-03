#include "../inc/cub3d.h"

int init_about_mlx(t_total *total)
{
	total->mlx = malloc(sizeof(t_mlx));
	total->mlx->mlx_ptr = mlx_init();
    total->mlx->win_ptr = mlx_new_window(total->mlx->mlx_ptr, 800, 600, "Raycasting Test");
	return (1);
}