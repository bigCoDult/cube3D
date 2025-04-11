#include "../inc/cub3d.h"

// 키 이벤트 처리 함수
int	key_press(int keycode, t_total *total)
{
	double	movespeed;
	double	rotspeed;
	t_ray	*ray;
	double	olddirx;
	double	oldplanex;

	ray = (t_ray *)total->ray;
	movespeed = 0.05;
	rotspeed = 0.03;
	printf("키코드: %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		mlx_loop_end(total->mlx->mlx_ptr);
	else if (keycode == 3768 || keycode == 126 || keycode == 119)
	{
		if (ray->map_data
			[(int)(ray->posY)][(int)(ray->posX + ray->dirX * movespeed)] != '1')
			ray->posX += ray->dirX * movespeed;
		if (ray->map_data
			[(int)(ray->posY + ray->dirY * movespeed)][(int)(ray->posX)] != '1')
			ray->posY += ray->dirY * movespeed;
	}
	else if (keycode == 3748 || keycode == 125 || keycode == 115)
	{
		if (ray->map_data
			[(int)(ray->posY)][(int)(ray->posX - ray->dirX * movespeed)] != '1')
			ray->posX -= ray->dirX * movespeed;
		if (ray->map_data
			[(int)(ray->posY - ray->dirY * movespeed)][(int)(ray->posX)] != '1')
			ray->posY -= ray->dirY * movespeed;
	}
	else if (keycode == 3761 || keycode == 123 || keycode == 97)
	{
		olddirx = ray->dirX;
		oldplanex = ray->planeX;
		ray->dirX = ray->dirX * cos(-rotspeed) - ray->dirY * sin(-rotspeed);
		ray->dirY = olddirx * sin(-rotspeed) + ray->dirY * cos(-rotspeed);
		ray->planeX
			= ray->planeX * cos(-rotspeed) - ray->planeY * sin(-rotspeed);
		ray->planeY = oldplanex * sin(-rotspeed) + ray->planeY * cos(-rotspeed);
	}
	else if (keycode == 3767 || keycode == 124 || keycode == 100)
	{
		olddirx = ray->dirX;
		oldplanex = ray->planeX;
		ray->dirX = ray->dirX * cos(rotspeed) - ray->dirY * sin(rotspeed);
		ray->dirY = olddirx * sin(rotspeed) + ray->dirY * cos(rotspeed);
		ray->planeX = ray->planeX * cos(rotspeed) - ray->planeY * sin(rotspeed);
		ray->planeY = oldplanex * sin(rotspeed) + ray->planeY * cos(rotspeed);
	}
	raycast(total);
	return (0);
}

// 창 닫기 이벤트 처리 함수
int	close_window(t_total *total)
{
	mlx_loop_end(total->mlx->mlx_ptr);
	return (0);
}

// 플레이어 위치 및 방향 초기화
void	init_player(t_ray *ray)
{
	int		y;
	int		x;
	char	player_char;

	y = 0;
	player_char = '\0';
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
				break ;
			}
			x++;
		}
		if (player_char)
			break ;
		y++;
	}
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
		ray->posX = 2;
		ray->posY = 2;
		ray->dirX = -1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = 0.66;
	}
}
