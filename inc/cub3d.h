/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 06:53:22 by yutsong           #+#    #+#             */
/*   Updated: 2025/04/15 18:33:13 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_mem_node
{
	void				*ptr;
	size_t				size;
	char				*label;
	struct s_mem_node	*next;
}	t_mem_node;

typedef struct s_mem_tracker
{
	t_mem_node	*head;
	int			count;
	size_t		total_size;
}	t_mem_tracker;

typedef struct s_ray
{
	double	posx;
	double	posy;
	int		mapx;
	int		mapy;
	double	dirx;
	double	diry;
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;
	double	camerax;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		screenwidth;
	int		screenheight;
	int		screenx;
	int		drawstart;
	int		drawend;
	int		lineheight;
	int		texnum;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	char	**map_data;
	int		map_width;
	int		map_height;
	void	**tex_imgs;
	int		**textures;
	int		tex_width;
	int		tex_height;
	int		ceiling_color;
	int		floor_color;
}	t_ray;

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
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*ceiling;
	char	*floor;
	char	*file;
}	t_extracted_str;

typedef struct s_image_info
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	char	*ceiling;
	char	*floor;
}	t_image_info;

typedef struct s_parsed
{
	t_image_info	*image_info;
	t_extracted_str	*extracted_str;
	char			**map;
	t_cordi			*player;
	int				direction;
	t_cordi			max;
}	t_parsed;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_total
{
	t_parsed		*parsed;
	t_mlx			*mlx;
	t_ray			*ray;
	t_mem_tracker	*mem_tracker;
}	t_total;

// extract
int		extract_str(int fd, t_total *total);
void	extract_map(char *file, t_total *total);
void	extract_img(t_total *total);
int		find_i_key(char *file, const char *key);
int		find_map_start(char *file, int i);
// validate
int		validate(t_total *total);
int		ft_atohex(char *hex);
int		is_map_part(char c);
int		is_closed(t_total *total);
int		is_no_trash(t_total *total);
int		if_failed_free(t_total *total);
int		is_one_player(t_total *total);
int		count_comma(char *str);


// free_both_case.c
void	free_success_case(t_total *total);
void	free_fail_case(t_total *total);
int		init_about_mlx(t_total *total);
void	print_parsed(t_total *total);
void	start_raycast(t_total *total);
// control.c
void	init_player(t_ray *ray);
void	set_player_direction(t_ray *ray, char player_char);
// control_set.c
void	set_north_direction(t_ray *ray);
void	set_south_direction(t_ray *ray);
void	set_east_direction(t_ray *ray);
void	set_west_direction(t_ray *ray);
void	set_default_player(t_ray *ray);
// control_player.c
void	move_forward(t_ray *ray, double movespeed);
void	move_backward(t_ray *ray, double movespeed);
void	rotate_left(t_ray *ray, double rotspeed);
void	rotate_right(t_ray *ray, double rotspeed);
int		key_press(int keycode, t_total *total);
// render.c
void	init_image(t_total *total, t_ray *ray);
void	load_textures(t_total *total, t_ray *ray);
int		get_texture_index(t_ray *ray);
// render_draw.c
void	draw_ceiling(t_ray *ray, int x);
void	draw_floor(t_ray *ray, int x);
void	draw_wall_texture(t_ray *ray, int x, int tex_idx);
void	draw_wall(t_ray *ray, int x);
// raycast.c
void	raycast(t_total *total);
void	init_ray(t_total *total, t_ray *ray, int x);
// raycast_wrap.c
int		game_loop(t_total *total);
int		close_window(t_total *total);
// raycast_cal.c
void	calculate_step(t_ray *ray);
void	cal_distance(t_ray *ray);
void	cal_wall_height(t_ray *ray);
void	cal_wall_texture(t_ray *ray);
// raycast_utils.c
void	dda(t_ray *ray);
// memory.c
void	init_mem_tracker(t_total *total);
void	*tracked_malloc(t_total *total, size_t size, char *label);
void	free_all_memory(t_total *total);
// memory_punish.c
void	tracked_free(t_total *total, void *ptr);
// memory_track.c
void	tracked_free(t_total *total, void *ptr);
// memory_free.c
void	free_success_case(t_total *total);
void	free_fail_case(t_total *total);
#endif /* CUB3D_H */
