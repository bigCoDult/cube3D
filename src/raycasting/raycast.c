// 광선 방향 벡터 : 광선이 바라보는 방향
ray_dir_x;
ray_dir_y;
// 플레이어 방향 벡터 : 플레이어가 바라보는 방향
player_dir_x;
player_dir_y;
// 카메라 평면 벡터 : 플레이어 시야폭
plane_x;
plane_y;
// 카메라 x좌표 : 정규화된, 화면x좌표
camera_x;

// 광선 초기화
void    init_ray(맵, 플레이어, 광선)
{
    // 카메라 평면 좌표 계산 : 화면의 X좌표를 -1 ~ 1 사이로 정규화
    // 광선 방향 벡터 계산
}

// DDA
void    dda(맵, 광선);
// 거리계산
void    cal_distance(광선);
// 벽 높이 및 텍스쳐 좌표 계산
void    cal_wall(광선);
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