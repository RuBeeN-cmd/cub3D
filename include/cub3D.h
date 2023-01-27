#ifndef CUB3D_H
#define CUB3D_H

#define PI 3.14159265359
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define COLOR_MASK 0xff00ff
#define FOV 90.0
#define KEY_W 1
#define KEY_A 2
#define KEY_S 4
#define KEY_D 8

#include "../mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

typedef struct	s_intersect
{
	float		dist;
	float		wall_height;
	struct s_intersect	*next;
}				t_intersect;

typedef struct	s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct	s_ray
{
	t_point	start;
	t_point vector;
}				t_ray;

typedef struct	s_player
{
	t_point	pos;
	t_point	dir;
}				t_player;

typedef struct	s_map
{
	float	**map;
	int		width;
	int		height;
}				t_map;

typedef struct	s_img
{
	void	*img;
	int		width;
	int		height;
	char	*buf;
	int		endian;
	int		line_len;
	int		pixel_bits;
}				t_img;

typedef struct	s_text
{
	char	*text;
	int		pos_y;
	int		pos_x;
	t_img	*sprite;
}				t_text;

typedef struct	s_game
{
	t_player	player;
	t_map		map;
	t_img		enemy_sprite;
	t_text		text;
}				t_game;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
	t_game	game;
	float	fov;
	int		key_press;
}				t_data;

// sprite.c
void	draw_sprite(t_data *data, int pos_y, int pos_x, t_img sprite);

// vector.c
t_point	rotate_vector(float angle, t_point vector);

//proto text !
void	draw_text(t_data *data, t_text *text);
void	load_sprite(t_data *data, t_img *img, char *sprite_path);

// data.c
void	init_data(t_data *data, int argc, char *argv[]);
void	destroy_data(t_data data);

// hook.c
int		key_hook_press(int keycode, t_data *data);
int		key_hook_release(int keycode, t_data *data);
int		button_hook(int keycode, int x, int y, t_data *data);
int		mouse_move_hook(int x, int y, t_data *data);
int		render_next_frame(t_data *data);

// image.c
void	create_new_image(t_data *data);
void	destroy_image(t_data *data);

// draw.c
void	draw_sky_ground(t_data *data, int sky_color, int ground_color);

// game.c
void	create_game(t_game *game, int argc, char *argv[]);

// file_utils.c
char	*read_file(char *path);

// str_utils.c
char	*ft_strdup(const char *s);
void	realloc_str(char **str_ptr, int size_to_add);
int		ft_strlen(char *str);
char 	*ft_strcpy(char *dest, const char *src);

// float_utils.c
float	get_min(float f1, float f2);

//render.c
void	draw_map(t_data *data);

#endif
