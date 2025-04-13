/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:21:53 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:23:09 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_img(t_total *total)
{
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->img);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[0]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[1]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[2]);
	mlx_destroy_image(total->mlx->mlx_ptr, total->ray->tex_imgs[3]);
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str);
}

void	free_wall(t_total *total)
{
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->north);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->south);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->east);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->west);
	free(total->parsed->image_info->ceiling);
	free(total->parsed->image_info->floor);
	free(total->parsed->image_info);
}

void	free_success_case(t_total *total)
{
	int	col;

	col = 0;
	free_img(total);
	free_wall(total);
	while (total->parsed->map[col] != NULL)
	{
		free(total->parsed->map[col]);
		col++;
	}
	free(total->parsed->map);
	free(total->parsed->player);
	free(total->parsed);
	mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
	mlx_destroy_display(total->mlx->mlx_ptr);
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
	{
		free(total->parsed->map[col]);
		col++;
	}
	free(total->parsed->map);
	free(total->parsed->player);
	free(total->parsed);
	free_all_memory(total);
	free(total->mem_tracker);
	free(total);
}
