/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsong <yutsong@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:15:11 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/13 05:50:08 by yutsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_total *total;
	int		fd;

	(void)argv;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d [map_file.cub]\n", 2);
		return (1);
	}
	fd = open("./img/map.cub", O_RDONLY);
	if (fd == -1)
	{
		printf("file open error\n");
		return (-1);
	}
	total = (t_total *)malloc(sizeof(t_total));
	init_mem_tracker(total);
	// 맵에서 str 추출
	if (extract_str(fd, total) == -1)
		return (1);
	if (validate(total))
	{
		init_about_mlx(total);
		extract_img(total);
		start_raycast(total);
		mlx_loop(total->mlx->mlx_ptr);
	}
	else
	{
		free_fail_case(total);
		close(fd);
		return (1);
	}
	free_success_case(total);
	close(fd);
	return (0);
}
