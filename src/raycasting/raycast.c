typedef struct s_ray
{
    // 플레이어 초기 위치 좌표
    int posX;
    int posY;
    // 맵 상 좌표
    int mapX;
    int mapY;
    // 플레이어의 초기 방향 벡터
    int dirX;
    int dirY;
    // 광선 방향 벡터 : 광선이 바라보는 방향
    int rayDirX;
    int rayDirY;
    // 플레이어 방향 벡터 : 플레이어가 바라보는 방향
    int playerDirX;
    int playerDirY;
    // 카메라 평면 벡터 : 플레이어 시야폭
    int planeX;
    int planeY;
    // 카메라 x좌표 : 정규화된, 화면x좌표
    int cameraX;
    // 현재 위치로부터 다음 X면 혹은 Y면까지의 광선의 길이
    int sideDistX;
    int sideDistY;
    // 어느 한 X면 혹은 Y면으로부터 다음 X 혹은 Y면까지의 광선의 길이
    int deltaDistX;
    int deltaDistY;
    // 카메라 평면까지의 수직거리
    int perpWallDist;
    // X 혹은 Y 방향으로의 진행
    int stepX;
    int stepY;
    // 벽 도달 여부
    int hit;
    // X축 벽인지 Y축 벽인지 여부
    int side;
    // 스크린 가로 크기
    int screenWidth;
    // 스크린 가로상 위치
    int screenX;
}   t_ray;


// 광선 초기화
void    init_ray(맵, 플레이어, 광선)
{
    int dirX;
    int dirY;

    screenX = 0;
    // 카메라 평면 좌표 계산 : 화면의 X좌표를 -1 ~ 1 사이로 정규화
    cameraX = 2 * screenX / screenWidth - 1;
    // 광선 방향 벡터 계산
    rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;
    // 현재 맵 그리드 좌표
    mapX = posX;
    mapY = posY;
    // 다음 그리드까지 거리 : fabs는 절대값 구하는 함수
    deltaDistX = fabs(1 / dirX);
    deltaDistY = fabs(1 / dirY);
    // 충돌 여부
    hit = 0;
}

// DDA
void    dda(맵, 광선, posX, posY)
{
    while (hit == 0)
    {
        // X 평면과의 거리가 더 가까울때
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // 벽에 닿았나 ?
        if (worldMap[mapX][mapY] > 0)
            hit = 1;
    }
}
// 거리계산
void    cal_distance(광선)
{
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
}
// 벽 높이 및 텍스쳐 좌표 계산
void    cal_wall_height(광선)
{
    int lineHeight = (h / perpWallDist);
    int drawStart = -lineHeight / 2 + h / 2;

    if (drawStart < 0)
        drawStart = 0;

    int drawEnd = lineHeight / 2 + h / 2;
    if (drawEnd >= h)
        drawEnd = h - 1;
}
// 메인 레이캐스팅 함수
void    raycast(맵, 플레이어, 광선)
{
    int width;

    width = 0;
    while (width < screen_width)
    {
        init_ray(맵, 플레이어, 광선);
        dda(맵, 광선);
        cal_distance(광선);
        cal_wall(광선);
        draw_wall(광선);
        width++;
    }
}