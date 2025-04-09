/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_both_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:10:42 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/09 20:14:27 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_total(t_total *total)
{
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->img);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[0]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[1]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[2]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[3]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->north);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->south);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->east);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->west);
	mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
	mlx_destroy_display(total->mlx->mlx_ptr);
}

void	free_success_case(t_total *total)
{
	int	col;

	col = 0;
	destroy_total(total);
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str);
	free(total->parsed->image_info->ceiling);
	free(total->parsed->image_info->floor);
	free(total->parsed->image_info);
	while (total->parsed->map[col] != NULL)
		free(total->parsed->map[col++]);
	free(total->parsed->map);
	free(total->parsed->player);
	free(total->parsed);
	free(total->mlx->mlx_ptr);
	free(total->mlx);
	print_mem_status(total);
	free_all_memory(total);
	free(total->mem_tracker);
	free(total);
}

void	free_fail_case(t_total *total)
{
	int	col;

	col = 0;
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str);
	while (total->parsed->map[col] != NULL)
		free(total->parsed->map[col++]);
	free(total->parsed->map);
	free(total->parsed->player);
	free(total->parsed);
	free_all_memory(total);
	free(total->mem_tracker);
	free(total);
}
