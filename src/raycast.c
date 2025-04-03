#include "../inc/cub3d.h"

// 함수 전방 선언
void    raycast(t_total *total);

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

// 이미지 초기화 함수
void    init_image(t_total *total, t_ray *ray)
{
    ray->screenWidth = 800;
    ray->screenHeight = 600;
    ray->img = mlx_new_image(total->mlx->mlx_ptr, ray->screenWidth, ray->screenHeight);
    ray->data = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->size_line, &ray->endian);
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

// 광선의 방향과 시작 지점에서의 사이드 거리 계산
void    calculate_step(t_ray *ray)
{
    // X 방향 스텝 및 최초 사이드 거리 설정
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
    }
    
    // Y 방향 스텝 및 최초 사이드 거리 설정
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
    }
}

// DDA
void    dda(t_ray *ray)
{
    while (ray->hit == 0)
    {
        // X 평면과의 거리가 더 가까울때
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        // 벽에 닿았나 확인
        if (ray->mapY >= 0 && ray->mapY < ray->map_height && 
            ray->mapX >= 0 && ray->mapX < ray->map_width &&
            ray->map_data[ray->mapY][ray->mapX] == '1')
            ray->hit = 1;
    }
}

// 거리계산
void    cal_distance(t_ray *ray)
{
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

// 벽 높이 및 텍스쳐 좌표 계산
void    cal_wall_height(t_ray *ray)
{
    ray->lineHeight = (int)(ray->screenHeight / ray->perpWallDist);
    ray->drawStart = -ray->lineHeight / 2 + ray->screenHeight / 2;

    if (ray->drawStart < 0)
        ray->drawStart = 0;

    ray->drawEnd = ray->lineHeight / 2 + ray->screenHeight / 2;
    if (ray->drawEnd >= ray->screenHeight)
        ray->drawEnd = ray->screenHeight - 1;
}

// 벽 텍스처 계산 함수 추가
void    cal_wall_texture(t_ray *ray)
{
    // 벽이 맞은 정확한 위치
    if (ray->side == 0)
        ray->wallX = ray->posY + ray->perpWallDist * ray->rayDirY;
    else
        ray->wallX = ray->posX + ray->perpWallDist * ray->rayDirX;
    ray->wallX -= floor(ray->wallX);
    
    // 텍스처 x 좌표
    ray->texX = (int)(ray->wallX * 64.0); // 64는 텍스처 너비
    if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1 && ray->rayDirY < 0))
        ray->texX = 64 - ray->texX - 1; // 64는 텍스처 너비
    
    // 텍스처 y 좌표 매핑을 위한 스텝 계산
    ray->step = 1.0 * 64 / ray->lineHeight; // 64는 텍스처 높이
    // 텍스처의 시작 위치
    ray->texPos = (ray->drawStart - ray->screenHeight / 2 + ray->lineHeight / 2) * ray->step;
}

// 텍스처 로드 함수
void    load_textures(t_total *total, t_ray *ray)
{
    int width, height;
    
    // 텍스처 로드를 위한 포인터 초기화
    ray->textures = (int **)malloc(sizeof(int *) * 4);
    ray->tex_imgs = (void **)malloc(sizeof(void *) * 4);
    
    // 북쪽 텍스처
    ray->tex_imgs[0] = mlx_xpm_file_to_image(total->mlx->mlx_ptr, 
                       total->parsed->extracted_str->north, &width, &height);
    ray->textures[0] = (int *)mlx_get_data_addr(ray->tex_imgs[0], 
                       &ray->bpp, &ray->size_line, &ray->endian);
    
    // 남쪽 텍스처
    ray->tex_imgs[1] = mlx_xpm_file_to_image(total->mlx->mlx_ptr, 
                       total->parsed->extracted_str->south, &width, &height);
    ray->textures[1] = (int *)mlx_get_data_addr(ray->tex_imgs[1], 
                       &ray->bpp, &ray->size_line, &ray->endian);
    
    // 서쪽 텍스처
    ray->tex_imgs[2] = mlx_xpm_file_to_image(total->mlx->mlx_ptr, 
                       total->parsed->extracted_str->west, &width, &height);
    ray->textures[2] = (int *)mlx_get_data_addr(ray->tex_imgs[2], 
                       &ray->bpp, &ray->size_line, &ray->endian);
    
    // 동쪽 텍스처
    ray->tex_imgs[3] = mlx_xpm_file_to_image(total->mlx->mlx_ptr, 
                       total->parsed->extracted_str->east, &width, &height);
    ray->textures[3] = (int *)mlx_get_data_addr(ray->tex_imgs[3], 
                       &ray->bpp, &ray->size_line, &ray->endian);
    
    // 텍스처 크기 저장 (모든 텍스처는 동일한 크기로 가정)
    ray->tex_width = width;
    ray->tex_height = height;
}

// 벽 그리기 함수
void    draw_wall(t_ray *ray, int x)
{
    int y;
    int color;
    int tex_idx;
    int tex_x, tex_y;

    // 어떤 텍스처를 사용할지 결정
    if (ray->side == 0 && ray->rayDirX > 0)
        tex_idx = 0; // 북쪽
    else if (ray->side == 0 && ray->rayDirX < 0)
        tex_idx = 1; // 남쪽
    else if (ray->side == 1 && ray->rayDirY > 0)
        tex_idx = 2; // 서쪽
    else
        tex_idx = 3; // 동쪽

    // 천장 그리기 (검은색)
    y = 0;
    while (y < ray->drawStart)
    {
        ray->data[y * ray->screenWidth + x] = 0x000000;
        y++;
    }

    // 벽 그리기
    y = ray->drawStart;
    while (y < ray->drawEnd)
    {
        // 텍스처 y 좌표 계산
        ray->texY = (int)ray->texPos & (ray->tex_height - 1);
        ray->texPos += ray->step;
        
        // 텍스처에서 색상 가져오기
        tex_x = ray->texX;
        tex_y = ray->texY;
        
        // 텍스처 배열에서 색상 가져오기
        if (ray->textures && ray->textures[tex_idx])
            color = ray->textures[tex_idx][tex_y * ray->tex_width + tex_x];
        else
        {
            // 텍스처가 없을 경우 대체 색상 사용
            if (tex_idx == 0)
                color = 0xFF0000; // 빨간색 (북)
            else if (tex_idx == 1)
                color = 0x00FF00; // 녹색 (남)
            else if (tex_idx == 2)
                color = 0x0000FF; // 파란색 (서)
            else
                color = 0xFFFF00; // 노란색 (동)
        }
        
        // 측면 벽은 더 어둡게
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F; // 어둡게 처리
        
        // 픽셀 설정
        ray->data[y * ray->screenWidth + x] = color;
        y++;
    }

    // 바닥 그리기 (회색)
    while (y < ray->screenHeight)
    {
        ray->data[y * ray->screenWidth + x] = 0x444444;
        y++;
    }
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

// 키 이벤트 처리 함수
int     key_press(int keycode, t_total *total)
{
    double moveSpeed = 0.05;
    double rotSpeed = 0.03;
    t_ray *ray = (t_ray *)total->ray;

    printf("키코드: %d\n", keycode); // 디버깅용

    // macOS 키 코드
    // ESC로 종료
    if (keycode == 53 || keycode == 65307) // ESC 키
    {
        mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
        exit(0);
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
    mlx_destroy_window(total->mlx->mlx_ptr, total->mlx->win_ptr);
    exit(0);
    return (0);
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
    total->ray = (t_ray *)malloc(sizeof(t_ray));
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