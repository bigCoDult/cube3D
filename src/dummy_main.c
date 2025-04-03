#include "../inc/cub3d.h"

/*
make 대신 사용한 임시 컴파일 명령어

cc -g dummy_main.c extract_map.c extract_str.c extract_img.c validate.c ../libft/libft.a ../minilibx-linux/libmlx_Linux.a -lX11 -lXext -lXrandr

cc -g dummy_main.c extract_map.c extract_str.c extract_img.c ../libft/libft.a ../minilibx-linux/libmlx_Darwin.a -I/opt/X11/include -L/opt/X11/lib -lX11 -lXext -lXrandr

mlx 오류 해결
	int	mlx_int_anti_resize_win() 안에 memset(&hints, 0, sizeof(hints)); 이 라인 추가
*/
int	main2(void)
{
	t_total	*total;
	int		fd;
	
	fd = open("./img/map.cub", O_RDONLY);
	if (fd == -1)
	{
		printf("file open error\n");
		return (-1);
	}
	total = (t_total *)ft_calloc(sizeof(t_total), 1);
	
	total->parsed = malloc(sizeof(t_parsed));
	
	extract_str(fd, total);
	print_parsed(total);

	if(validate(total))
		init_about_mlx(total);
	
	
	
	int col = 0;
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
