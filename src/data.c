#include "../include/cub3D.h"

static void	set_hook(t_data *data)
{
	mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1, key_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
}

void	load_sprite(t_data *data, t_img *img, char *sprite_path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, sprite_path, &img->width, &img->height);
	img->buf = mlx_get_data_addr(img->img, &img->pixel_bits, &img->line_len, &img->endian);
}

void	init_data(t_data *data, int argc, char *argv[])
{

	create_game(&data->game, argc, argv);
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	set_hook(data);
	load_sprite(data, &data->game.enemy_sprite, "asset/sprite/player_0.xpm");

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
	data->game.map.map[47][47] = 1.0;
	data->game.map.map[47][48] = 1.0;
	data->game.map.map[47][49] = 1.0;
	data->game.map.map[47][50] = 1.0;
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

	data->game.player.pos.x = 50;
	data->game.player.pos.x = 50;



	create_new_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	destroy_data(t_data data)
{
	int i;
	
	i = 0;
	while (i < 3)
	{
		free(data.game.map.map[i]);
		i++;
	}
	free(data.game.map.map);

	mlx_destroy_image(data.mlx, data.game.enemy_sprite.img);
	mlx_clear_window(data.mlx, data.win);
	destroy_image(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
