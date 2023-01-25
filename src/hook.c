#include "../include/cub3D.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_loop_end(data->mlx);
	return (0);
}

void	put_sprite(t_data *data, int pos_y, int pos_x, t_img sprite)
{
	int y = 0;
	int x = 0;
	int index = 0;

	while (y < sprite.height)
	{
			x = 0;
			while (x < sprite.width)
			{
				if (((int*)sprite.buf)[index] != COLOR_MASK)
					((int*)data->img.buf)[(pos_y + y) * data->img.width + (pos_x + x)] = ((int*)sprite.buf)[index];
				index++;
				x++;
			}
			y++;
	}
}

int	render_next_frame(t_data *data)
{
	draw_sky_ground(data, 0xace0e8, 0x254a08);
	put_sprite(data, 0, 0, data->game.enemy_sprite);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
