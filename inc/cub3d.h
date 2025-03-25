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

typedef struct s_data
{
	char *ceiling; /* "숫자,숫자,숫자" 이 형태의 문자열*/
	char *floor;
	int *floor; /* 파일 경로*/
	char *north;
	char *south;
	char *east;
	char *west;
} t_data;

typedef struct s_parsed
{
	t_data data;
	char **map;
} t_parsed;

#endif /* CUB3D_H */