#include <math.h>

// 미리 선언
typedef struct s_map t_map;
typedef struct s_player t_player;

typedef struct s_ray
{
    // 플레이어 위치 좌표
    double posX;
    double posY;
    // 맵 상 좌표
    int    mapX;
    int    mapY;
    // 플레이어의 방향 벡터
    double dirX;
    double dirY;
    // 광선 방향 벡터 : 광선이 바라보는 방향
    double rayDirX;
    double rayDirY;
    // 카메라 평면 벡터 : 플레이어 시야폭
    double planeX;
    double planeY;
    // 카메라 x좌표 : 정규화된, 화면x좌표
    double cameraX;
    // 현재 위치로부터 다음 X면 혹은 Y면까지의 광선의 길이
    double sideDistX;
    double sideDistY;
    // 어느 한 X면 혹은 Y면으로부터 다음 X 혹은 Y면까지의 광선의 길이
    double deltaDistX;
    double deltaDistY;
    // 카메라 평면까지의 수직거리
    double perpWallDist;
    // X 혹은 Y 방향으로의 진행
    int    stepX;
    int    stepY;
    // 벽 도달 여부
    int    hit;
    // X축 벽인지 Y축 벽인지 여부
    int    side;
    // 스크린 가로 크기
    int    screenWidth;
    int    screenHeight;
    // 스크린 가로상 위치
    int    screenX;
    // 벽 그리기 시작과 끝 지점
    int    drawStart;
    int    drawEnd;
    // 벽 높이
    int    lineHeight;
    // 텍스처 정보
    // 벽 방향 0:북 1:남 2:서 3:동
    int    texNum;
    // 충돌지점
    double wallX;
    // 텍스처 내부 좌표
    int    texX;
    int    texY;
    // 텍스처 매핑 비율
    double step;
    // 텍스처 매핑 위치
    double texPos;
}   t_ray;

// 광선 초기화
void    init_ray(t_map *map, t_player *player, t_ray *ray)
{
    ray->screenX = 0;
    // 카메라 평면 좌표 계산 : 화면의 X좌표를 -1 ~ 1 사이로 정규화
    ray->cameraX = 2 * ray->screenX / ray->screenWidth - 1;
    // 광선 방향 벡터 계산
    ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
    ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
    // 현재 맵 그리드 좌표
    ray->mapX = (int)ray->posX;
    ray->mapY = (int)ray->posY;
    // 다음 그리드까지 거리 : fabs는 절대값 구하는 함수
    ray->deltaDistX = fabs(1 / ray->rayDirX);
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
void    dda(t_map *map, t_ray *ray, double posX, double posY)
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
        // 벽에 닿았나 ? (worldMap 대신 map 구조체 내 적절한 필드 사용 필요)
        // if (map->worldMap[ray->mapX][ray->mapY] > 0)
        //     ray->hit = 1;
        ray->hit = 1; // 임시로 충돌 처리, 실제로는 맵 데이터 확인 필요
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

// 벽 그리기 함수
void    draw_wall(t_map *map, t_player *player, t_ray *ray, void *mlx, void *win, int x)
{
    int y;
    int color;

    // 벽 그리기
    y = ray->drawStart;
    while (y < ray->drawEnd)
    {
        // 텍스처 y 좌표 계산
        ray->texY = (int)ray->texPos & 63; // 64는 텍스처 높이
        ray->texPos += ray->step;
        
        // 텍스처 컬러 선택 (실제로는 텍스처 배열에서 가져옴)
        // color = textures[ray->texNum][ray->texY][ray->texX];
        
        // 측면 벽은 더 어둡게
        if (ray->side == 1)
            color = (color >> 1) & 8355711; // 어둡게 처리
        
        // mlx_pixel_put(mlx, win, x, y, color);
        y++;
    }
}

// 메인 레이캐스팅 함수
void    raycast(t_map *map, t_player *player, t_ray *ray)
{
    int width;

    width = 0;
    while (width < ray->screenWidth)
    {
        ray->screenX = width;
        init_ray(map, player, ray);
        calculate_step(ray);
        dda(map, ray, ray->posX, ray->posY);
        cal_distance(ray);
        cal_wall_height(ray);
        cal_wall_texture(ray);
        // draw_wall(map, player, ray, mlx, win, width);
        width++;
    }
}