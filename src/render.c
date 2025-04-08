#include "../inc/cub3d.h"

// 이미지 초기화 함수
void    init_image(t_total *total, t_ray *ray)
{
    ray->screenWidth = 800;
    ray->screenHeight = 600;
    ray->img = mlx_new_image(total->mlx->mlx_ptr, ray->screenWidth, ray->screenHeight);
    ray->data = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->size_line, &ray->endian);
}

// 텍스처 로드 함수
void    load_textures(t_total *total, t_ray *ray)
{
    int width;
    int height;
    
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
	ray->ceiling_color = ft_atohex(total->parsed->image_info->ceiling);
	ray->floor_color = ft_atohex(total->parsed->image_info->floor);
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
        ray->data[y * ray->screenWidth + x] = ray->ceiling_color;
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
        ray->data[y * ray->screenWidth + x] = ray->floor_color;
        y++;
    }
}