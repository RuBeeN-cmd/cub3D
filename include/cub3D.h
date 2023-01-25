#ifndef CUB3D_H
#define CUB3D_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define COLOR_MASK 0xff00ff

#include "../mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct	s_player
{
	float	x;
	float	y;
}				t_player;

typedef struct	s_map
{
	int	**map;
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

typedef struct	s_game
{
	t_player	player;
	t_map		map;
	t_img		enemy_sprite;
}				t_game;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
	t_game	game;
}				t_data;

// data.c
void	init_data(t_data *data, int argc, char *argv[]);
void	destroy_data(t_data data);

// hook.c
int		key_hook(int keycode, t_data *data);
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
void	realloc_str(char **str_ptr, int size_to_add);
int		ft_strlen(char *str);
char 	*ft_strcpy(char *dest, const char *src);

#endif
