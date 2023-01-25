#include "cub3D.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_loop_end(data->mlx);
	return (0);
}

int	render_next_frame(t_data *data)
{
	draw_sky_ground(data, 0xace0e8, 0x254a08);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}