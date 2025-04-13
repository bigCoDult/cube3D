/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wrap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:56:35 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 04:56:45 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 게임 루프 함수
int	game_loop(t_total *total)
{
	raycast(total);
	return (0);
}

// 창 닫기 이벤트 처리 함수
int	close_window(t_total *total)
{
	mlx_loop_end(total->mlx->mlx_ptr);
	return (0);
}
