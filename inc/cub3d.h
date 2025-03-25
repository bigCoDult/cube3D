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

typedef struct s_image_info
{
	char *ceiling; /* "숫자,숫자,숫자" 이 형태의 문자열*/
	char *floor;
	char *north; /* 파일 경로*/
	char *south;
	char *east;
	char *west;
} t_image_info;

typedef struct s_parsed
{
	t_image_info image_info;
	char **map;
	t_cordi *player;
	int direction; // 플레이어가 바라보고 있는 방향 = 게임을 시작했을때 보여야 하는 타일
} t_parsed;

typedef struct s_total // minishell에서의 t_shell과 같음
{
	t_parsed *parsed;
	// 필요한것 추가 바랍니다
} t_total;

#endif /* CUB3D_H */