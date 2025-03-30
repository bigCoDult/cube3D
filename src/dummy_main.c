#include "../../inc/cub3d.h"

// cc -g dummy_main.c extract_map.c extract_str.c extract_img.c ../../libft/libft.a ../../minilibx-linux/libmlx_Linux.a -lX11 -lXext -lXrandr
// cc -g dummy_main.c extract_map.c extract_str.c extract_img.c ../../libft/libft.a ../../minilibx-linux/libmlx_Darwin.a -I/opt/X11/include -L/opt/X11/lib -lX11 -lXext -lXrandr
// make 대신 사용한 임시 컴파일 명령어
int	main(void)
{
	t_total	*total;
	int		fd;

	fd = open("../../img/map.cub", O_RDONLY);
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	total->parsed = malloc(sizeof(t_parsed));
	total->parsed->extracted_str = malloc(sizeof(t_extracted_str));
	if (extract_str(fd, total) == -1)
	{
		// free(total->parsed->extracted_str);
		free(total->parsed);
		free(total);
		close(fd);
		return (-1);
	}
	printf("------------str start------------\n");
	printf("north: %s\n", total->parsed->extracted_str->north);
	printf("south: %s\n", total->parsed->extracted_str->south);
	printf("west: %s\n", total->parsed->extracted_str->west);
	printf("east: %s\n", total->parsed->extracted_str->east);
	printf("floor: %s\n", total->parsed->extracted_str->floor);
	printf("ceiling: %s\n", total->parsed->extracted_str->ceiling);
	printf("------------str end------------\n");
	
	printf("\n\n\n");
	
	int row = 0;
	int col = 0;
	printf("------------map start------------\n");
	while (total->parsed->map[col] != NULL)
	{
		printf("%s\n", total->parsed->map[col]);
		col++;
	}
	printf("------------map end------------\n");
	
	
	total->mlx = malloc(sizeof(t_mlx));
	total->mlx->mlx_ptr = mlx_init();
	total->mlx->win_ptr = mlx_new_window(total->mlx->mlx_ptr, 1000, 500, "pokemon mountain");
	extract_img(total);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->north, 0, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->south, 64, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->west, 0, 64);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->east, 64, 64);
	mlx_loop(total->mlx->mlx_ptr);
	col = 0;
	while (total->parsed->map[col] != NULL)
	{
		free(total->parsed->map[col]);
		col++;
	}
	free(total->parsed->map);
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str);
	free(total->parsed);
	free(total);
	close(fd);
	return (0);
}
