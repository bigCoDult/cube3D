#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_cordi
{
	int	row;
	int	col;
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
	// 필요한것 추가 바랍니다
} t_total;

int		extract_str(int fd, t_total *total);
void	extract_map(char *file, t_total *total);
void	extract_img(t_total *total);


#endif /* CUB3D_H */
