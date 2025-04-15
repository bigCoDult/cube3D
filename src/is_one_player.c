/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_one_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:46:25 by sanbaek           #+#    #+#             */
/*   Updated: 2025/04/15 16:47:18 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_one_player(t_total *total)
{
	int	i;
	int	k;
	int	player_count;

	i = 0;
	player_count = 0;
	while (total->parsed->map[i])
	{
		k = 0;
		while (total->parsed->map[i][k])
		{
			if (total->parsed->map[i][k] == 'N' || total->parsed->map[i][k] \
			== 'S' || total->parsed->map[i][k] == 'E' || \
			total->parsed->map[i][k] == 'W')
				player_count++;
			k++;
		}
		i++;
	}
	return (player_count == 1);
}
