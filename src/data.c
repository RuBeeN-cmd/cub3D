#include "../include/cub3D.h"

static void	set_hook(t_data *data)
{
	mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1, key_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
}

void	init_data(t_data *data, int argc, char *argv[])
{

	create_game(&data->game, argc, argv);
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	set_hook(data);
	create_new_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	destroy_data(t_data data)
{
	mlx_clear_window(data.mlx, data.win);
	destroy_image(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
