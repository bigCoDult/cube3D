#include "../inc/cub3d.h"

// 더미 맵 생성
void create_dummy_map(t_total *total, t_ray *ray)
{
    // 더미 맵 데이터 생성
    // char *map_data[] = {
    //     "11111111111111111111111111111111",
    //     "10000000000000000000000000000001",
    //     "10000000000000000000000000000001",
    //     "10000111100001100000000000000001",
    //     "10000100100001100000000000000001",
    //     "10000111100001100000000000000001",
    //     "10000100000001100000000000000001",
    //     "10000111100001100000000000000001",
    //     "10000000000000000000000000000001",
    //     "10000000000000000001111000000001",
    //     "10000000000000000000000000000001",
    //     "10000000000000000000000000000001",
    //     "10000000000000000N00000000000001",
    //     "10000000000000000000000000000001",
    //     "10000000000000000000000000000001",
    //     "10000000000000000000000000000001",
    //     "11111111111111111111111111111111",
    //     NULL
    // };

    // // 맵 할당 및 복사
    // int i = 0;
    // while (map_data[i])
    //     i++;
    
    // total->parsed = malloc(sizeof(t_parsed));
    // total->parsed->map = malloc(sizeof(char *) * (i + 1));
    
    // i = 0;
    // while (map_data[i])
    // {
    //     total->parsed->map[i] = ft_strdup(map_data[i]);
    //     i++;
    // }
    // total->parsed->map[i] = NULL;
    
    // ray 구조체에 맵 정보 저장
    ray->map_data = total->parsed->map;
    // ray->map_height = i;
    // ray->map_width = ft_strlen(map_data[0]);
	int col = 0;
	ray->map_width = 0;
	while (total->parsed->map[col] != NULL)
	{
		if (ray->map_width < (int)ft_strlen(total->parsed->map[col]))
			ray->map_width = (int)ft_strlen(total->parsed->map[col]);
		col++;
	}
	ray->map_height = col;
}


// 광선 초기화
void    init_ray(t_total *total, t_ray *ray, int x)
{
	(void)total;
    ray->screenX = x;
    // 카메라 평면 좌표 계산 : 화면의 X좌표를 -1 ~ 1 사이로 정규화
    ray->cameraX = 2 * ray->screenX / (double)ray->screenWidth - 1;
    // 광선 방향 벡터 계산
    ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
    ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
    // 현재 맵 그리드 좌표
    ray->mapX = (int)ray->posX;
    ray->mapY = (int)ray->posY;
    // 다음 그리드까지 거리 : fabs는 절대값 구하는 함수
    if (ray->rayDirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1 / ray->rayDirX);
    if (ray->rayDirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1 / ray->rayDirY);
    // 충돌 여부
    ray->hit = 0;
}

// 메인 레이캐스팅 함수
void    raycast(t_total *total)
{
    int width;
    t_ray *ray = (t_ray *)total->ray;

    width = 0;
    while (width < ray->screenWidth)
    {
        init_ray(total, ray, width);
        calculate_step(ray);
        dda(ray);
        cal_distance(ray);
        cal_wall_height(ray);
        cal_wall_texture(ray);
        draw_wall(ray, width);
        width++;
    }
    
    // 그려진 이미지를 화면에 표시
    mlx_put_image_to_window(total->mlx->mlx_ptr, total->mlx->win_ptr, ray->img, 0, 0);
}



// 게임 루프 함수
int     game_loop(t_total *total)
{
    raycast(total);
    return (0);
}

// 레이캐스팅 시작 함수
void    start_raycast(t_total *total)
{
    // 레이 구조체 할당
    // total->ray = (t_ray *)malloc(sizeof(t_ray));
    total->ray = tracked_malloc(total, sizeof(t_ray), "ray");
    t_ray *ray = (t_ray *)total->ray;
    
    // 더미 맵 생성
    create_dummy_map(total, ray);
    
    // 이미지 초기화
    init_image(total, ray);
    
    // 플레이어 초기화
    init_player(ray);
    
    // 텍스처 로드
    load_textures(total, ray);
    
    // 키 이벤트 등록 (macOS 방식)
    mlx_hook(total->mlx->win_ptr, 2, 1L<<0, key_press, total);  // 키를 누를 때
    mlx_hook(total->mlx->win_ptr, 17, 0, close_window, total);  // 창 닫기 버튼
    
    // 게임 루프 설정
    mlx_loop_hook(total->mlx->mlx_ptr, game_loop, total);
    
    // 초기 화면 그리기
    raycast(total);
}

// int main()
// {
//     t_total *total;

//     // 메모리 할당
//     total = (t_total *)malloc(sizeof(t_total));
//     total->mlx = malloc(sizeof(t_mlx));
    
//     // MLX 초기화
//     total->mlx->mlx_ptr = mlx_init();
//     total->mlx->win_ptr = mlx_new_window(total->mlx->mlx_ptr, 800, 600, "Raycasting Test");
    
//     // 레이캐스팅 설정 및 시작
//     start_raycast(total);
    
//     // MLX 루프 실행
//     mlx_loop(total->mlx->mlx_ptr);
    
//     return (0);
// }