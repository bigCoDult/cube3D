#include "../inc/cub3d.h"

// 키 이벤트 처리 함수
int     key_press(int keycode, t_total *total)
{
	double moveSpeed;
	double rotSpeed;
	t_ray *ray;

	ray = (t_ray *)total->ray;
	moveSpeed = 0.05;
	rotSpeed = 0.03;
	printf("키코드: %d\n", keycode); // 디버깅용

	// ESC로 종료
	if (keycode == 53 || keycode == 65307) // ESC 키
	{
		// mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
		// print_mem_status(total); // 디버깅용, 정리 전 메모리 상태 출력
		// free_all_memory(total);
		// free(total->mem_tracker);
		// free(total);
		// exit(0);
		mlx_loop_end(total->mlx->mlx_ptr);
	}
	// 앞으로 이동
	else if (keycode == 3768 || keycode == 126 || keycode == 119) // W 키 또는 위쪽 화살표
	{
		if (ray->map_data[(int)(ray->posY)][(int)(ray->posX + ray->dirX * moveSpeed)] != '1')
			ray->posX += ray->dirX * moveSpeed;
		if (ray->map_data[(int)(ray->posY + ray->dirY * moveSpeed)][(int)(ray->posX)] != '1')
			ray->posY += ray->dirY * moveSpeed;
	}
	// 뒤로 이동
	else if (keycode == 3748 || keycode == 125 || keycode == 115) // S 키 또는 아래쪽 화살표
	{
		if (ray->map_data[(int)(ray->posY)][(int)(ray->posX - ray->dirX * moveSpeed)] != '1')
			ray->posX -= ray->dirX * moveSpeed;
		if (ray->map_data[(int)(ray->posY - ray->dirY * moveSpeed)][(int)(ray->posX)] != '1')
			ray->posY -= ray->dirY * moveSpeed;
	}
	// 왼쪽으로 회전
	else if (keycode == 3761 || keycode == 123 || keycode == 97) // A 키 또는 왼쪽 화살표
	{
		double oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(-rotSpeed) - ray->dirY * sin(-rotSpeed);
		ray->dirY = oldDirX * sin(-rotSpeed) + ray->dirY * cos(-rotSpeed);
		double oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(-rotSpeed) - ray->planeY * sin(-rotSpeed);
		ray->planeY = oldPlaneX * sin(-rotSpeed) + ray->planeY * cos(-rotSpeed);
	}
	// 오른쪽으로 회전
	else if (keycode == 3767 || keycode == 124 || keycode == 100) // D 키 또는 오른쪽 화살표
	{
		double oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(rotSpeed) - ray->dirY * sin(rotSpeed);
		ray->dirY = oldDirX * sin(rotSpeed) + ray->dirY * cos(rotSpeed);
		double oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(rotSpeed) - ray->planeY * sin(rotSpeed);
		ray->planeY = oldPlaneX * sin(rotSpeed) + ray->planeY * cos(rotSpeed);
	}
	
	// 화면 다시 그리기
	raycast(total);
	return (0);
}

// 창 닫기 이벤트 처리 함수
int     close_window(t_total *total)
{
	// mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
	// print_mem_status(total); // 디버깅용, 정리 전 메모리 상태 출력
	// free_all_memory(total);
	// free(total->mem_tracker);
	// free(total);
	// exit(0);
	mlx_loop_end(total->mlx->mlx_ptr);
	return (0);
}

// 플레이어 위치 및 방향 초기화
void    init_player(t_ray *ray)
{
	// 맵에서 플레이어 위치 찾기 ('N', 'S', 'E', 'W')
	int y = 0;
	int x;
	char player_char = '\0';

	while (y < ray->map_height)
	{
		x = 0;
		while (x < ray->map_width && ray->map_data[y][x])
		{
			if (ray->map_data[y][x] == 'N' || ray->map_data[y][x] == 'S' ||
				ray->map_data[y][x] == 'E' || ray->map_data[y][x] == 'W')
			{
				player_char = ray->map_data[y][x];
				ray->posX = x + 0.5;
				ray->posY = y + 0.5;
				break;
			}
			x++;
		}
		if (player_char)
			break;
		y++;
	}
	
	// 방향 벡터 초기화
	if (player_char == 'N')
	{
		ray->dirX = 0;
		ray->dirY = -1;
		ray->planeX = 0.66;
		ray->planeY = 0;
	}
	else if (player_char == 'S')
	{
		ray->dirX = 0;
		ray->dirY = 1;
		ray->planeX = -0.66;
		ray->planeY = 0;
	}
	else if (player_char == 'E')
	{
		ray->dirX = 1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = 0.66;
	}
	else if (player_char == 'W')
	{
		ray->dirX = -1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = -0.66;
	}
	else
	{
		// 기본값 설정
		ray->posX = 2;
		ray->posY = 2;
		ray->dirX = -1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = 0.66;
	}
}