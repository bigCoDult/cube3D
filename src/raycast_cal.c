#include "../inc/cub3d.h"


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