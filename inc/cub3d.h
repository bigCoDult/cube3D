#ifndef CUB3D_H
# define CUB3D_H

// # include <X11/X.h>
// # include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
#include <math.h>

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
    // 이미지 정보
    void   *img;
    int    *data;
    int    bpp;
    int    size_line;
    int    endian;
    // 맵 데이터
    char   **map_data;
    int     map_width;
    int     map_height;
}   t_ray;

typedef struct s_cordi
{
	int	col;
	int	row;
}	t_cordi;

typedef enum e_direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
}	t_direction;

typedef struct s_extracted_str
{
	char *north; /* 파일 경로*/
	char *south;
	char *east;
	char *west;
	char *ceiling; /* "숫자,숫자,숫자" 이 형태의 문자열*/
	char *floor;
} t_extracted_str;

typedef struct s_image_info
{
	void *north; /* xpm 이미지 */
	void *south;
	void *east;
	void *west;
	char *ceiling; /* "숫자,숫자,숫자" 이 형태의 문자열*/
	char *floor;
} t_image_info;

typedef struct s_parsed
{
	t_image_info *image_info;
	t_extracted_str *extracted_str;
	char **map; // {' ', 1, 0, P}로 구성된 맵
	t_cordi *player; // 플레이어의 위치
	int direction; // 플레이어가 바라보고 있는 방향 = 게임을 시작했을때 보여야 하는 타일
} t_parsed;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
} t_mlx;

typedef struct s_total // minishell에서의 t_shell과 같음
{
	t_parsed *parsed;
	t_mlx *mlx;
	t_ray *ray;
	// 필요한것 추가 바랍니다
} t_total;

int		extract_str(int fd, t_total *total);
void	extract_map(char *file, t_total *total);
void	extract_img(t_total *total);
int	validate(t_total *total);


#endif /* CUB3D_H */
