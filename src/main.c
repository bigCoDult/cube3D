/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:15:11 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 15:51:55 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_and_execute(t_total *total, int fd)
{
	if (validate(total))
	{
		init_about_mlx(total);
		extract_img(total);
		start_raycast(total);
		mlx_loop(total->mlx->mlx_ptr);
		close(fd);
		return (0);
	}
	else
	{
		free_fail_case(total);
		close(fd);
		return (1);
	}
}

int	main(int argc, char **argv)
{
	t_total	*total;
	int		fd;

	(void)argv;
	if (argc != 2)
	{
		write(2, "Error\ninvalid argc\n", 19);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nmap path invalid\n", 23);
		return (1);
	}
	total = (t_total *)malloc(sizeof(t_total));
	init_mem_tracker(total);
	if (extract_str(fd, total) == -1)
		return (1);
	if (validate_and_execute(total, fd))
		return (1);
	free_success_case(total);
	close(fd);
	return (0);
}
