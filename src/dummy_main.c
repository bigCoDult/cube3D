#include "../inc/cub3d.h"

/*
make 대신 사용한 임시 컴파일 명령어

cc -g dummy_main.c extract_map.c extract_str.c extract_img.c validate.c ../libft/libft.a ../minilibx-linux/libmlx_Linux.a -lX11 -lXext -lXrandr

cc -g dummy_main.c extract_map.c extract_str.c extract_img.c ../libft/libft.a ../minilibx-linux/libmlx_Darwin.a -I/opt/X11/include -L/opt/X11/lib -lX11 -lXext -lXrandr

mlx 오류 해결
	int	mlx_int_anti_resize_win() 안에 memset(&hints, 0, sizeof(hints)); 이 라인 추가
*/
int	main(void)
{
	t_total	*total;
	int		fd;
	
	fd = open("../img/map.cub", O_RDONLY);
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	total->parsed = malloc(sizeof(t_parsed));
	total->parsed->extracted_str = malloc(sizeof(t_extracted_str));
	total->parsed->player = (t_cordi *)ft_calloc(sizeof(t_cordi), 1);
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
	
	
	printf("\n\n\n");
	if (total->parsed->player->col != 0)
		printf("player coordinate: %c %d, %d\n", total->parsed->map[total->parsed->player->col][total->parsed->player->row], total->parsed->player->col, total->parsed->player->row);
	else
		printf("player not found\n");
	printf("\n\n\n");
	
	
	
	
	total->mlx = malloc(sizeof(t_mlx));
	total->mlx->mlx_ptr = mlx_init();
	total->mlx->win_ptr = mlx_new_window(total->mlx->mlx_ptr, 300, 300, "pokemon mountain");
	extract_img(total);
	
	validate(total);
	
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->north, 0, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->south, 64, 0);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->west, 0, 64);
	mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, total->parsed->image_info->east, 64, 64);
	mlx_loop_end(total->mlx->mlx_ptr);
	mlx_loop(total->mlx->mlx_ptr);
	
	
	
	col = 0;
	while (total->parsed->map[col] != NULL)
	{
		free(total->parsed->map[col]);
		col++;
	}
	free(total->parsed->map);
	free(total->parsed->player);
	free(total->parsed->extracted_str->north);
	free(total->parsed->extracted_str->south);
	free(total->parsed->extracted_str->west);
	free(total->parsed->extracted_str->east);
	free(total->parsed->extracted_str->floor);
	free(total->parsed->extracted_str->ceiling);
	free(total->parsed->extracted_str);
	
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->north);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->south);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->west);
	mlx_destroy_image(total->mlx->mlx_ptr, total->parsed->image_info->east);
	mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
	mlx_destroy_display(total->mlx->mlx_ptr);
	
	free(total->mlx->mlx_ptr);
	free(total->mlx);
	free(total->parsed->image_info);
	free(total->parsed);
	free(total);
	close(fd);
	return (0);
}
