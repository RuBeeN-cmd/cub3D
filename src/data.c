#include "../include/cub3D.h"
#include <stdlib.h>

static void	set_hook(t_data *data)
{
	mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1, key_hook_press, data);
	mlx_hook(data->win, 3, 2, key_hook_release, data);
	mlx_hook(data->win, 4, 1<<2, button_hook, data);
	mlx_hook(data->win, 6, 1<<6, mouse_move_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
}

void	load_sprite(t_data *data, t_img *img, char *sprite_path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, sprite_path, &img->width, &img->height);
	img->buf = mlx_get_data_addr(img->img, &img->pixel_bits, &img->line_len, &img->endian);
}

void	init_text(t_data *data, t_text *text, const char *str, int x, int y)
{
	(void) data;
	(void) x;
	(void) y;
	text->text = ft_strdup(str);
	text->pos_x = x;
	text->pos_y = y;
	text->sprite = malloc(sizeof(t_img) * 3);
	load_sprite(data, &text->sprite[0], "asset/font/lower_font.xpm");
	load_sprite(data, &text->sprite[1], "asset/font/upper_font.xpm");
	load_sprite(data, &text->sprite[2], "asset/font/numeral_font.xpm");
}

void	destroy_text(t_data data, t_text text)
{
	mlx_destroy_image(data.mlx, text.sprite[0].img);
	mlx_destroy_image(data.mlx, text.sprite[1].img);
	free(text.sprite);
	free(text.text);
}

void	init_data(t_data *data, int argc, char *argv[])
{

	create_game(&data->game, argc, argv);
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->fov = FOV;
	data->key_press = 0;
	load_sprite(data, &data->game.enemy_sprite, "asset/sprite/player_0.xpm");
	init_text(data, &data->game.text, "XX", 10, 10);

	int i;
	int j;

	data->game.map.map = malloc(sizeof(float *) * (100 + 1));
	i = 0;
	while (i < 100)
	{
		data->game.map.map[i] = malloc(sizeof(float) * 100);
		j = 0;
		while (j < 100)
		{
			data->game.map.map[i][j] = 0;
			j++;
		}
		i++;
	}
	data->game.map.map[i] = NULL;
	data->game.map.map[47][47] = 0.5;
	data->game.map.map[47][48] = 1.0;
	data->game.map.map[47][49] = 2.0;
	data->game.map.map[47][50] = 3.0;
	data->game.map.map[47][51] = 1.0;
	data->game.map.map[47][52] = 1.0;
	data->game.map.map[47][53] = 1.0;
	data->game.map.map[48][47] = 1.0;
	data->game.map.map[48][53] = 1.0;
	data->game.map.map[49][47] = 1.0;
	data->game.map.map[49][53] = 1.0;
	data->game.map.map[50][47] = 1.0;
	data->game.map.map[50][53] = 1.0;
	data->game.map.map[51][47] = 1.0;
	data->game.map.map[51][53] = 1.0;
	data->game.map.map[52][47] = 1.0;
	data->game.map.map[52][53] = 1.0;
	data->game.map.map[53][47] = 1.0;
	data->game.map.map[53][48] = 1.0;
	data->game.map.map[53][49] = 1.0;
	data->game.map.map[53][50] = 1.0;
	data->game.map.map[53][51] = 1.0;
	data->game.map.map[53][52] = 1.0;
	data->game.map.map[53][53] = 1.0;
	data->game.map.width = 100;
	data->game.map.height = 100;

	data->game.player.pos.x = 50.5;
	data->game.player.pos.y = 50.5;
	data->game.player.dir.x = 0;
	data->game.player.dir.y = 1;


	create_new_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	set_hook(data);
	//mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, data->width / 2, data->height / 2);
}

void	destroy_data(t_data data)
{
	int i;
	
	i = 0;
	while (i < 100)
	{
		free(data.game.map.map[i]);
		i++;
	}
	destroy_text(data, data.game.text);
	free(data.game.map.map);
	mlx_destroy_image(data.mlx, data.game.enemy_sprite.img);
	mlx_clear_window(data.mlx, data.win);
	destroy_image(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
