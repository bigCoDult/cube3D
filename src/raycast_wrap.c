/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wrap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:56:35 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 07:37:06 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	game_loop(t_total *total)
{
	raycast(total);
	return (0);
}

int	close_window(t_total *total)
{
	mlx_loop_end(total->mlx->mlx_ptr);
	return (0);
}
