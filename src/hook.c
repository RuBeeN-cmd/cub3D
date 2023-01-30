#include "../include/cub3D.h"

int	key_hook_press(int keycode, t_data *data)
{
	if (keycode == 119)
		data->key_press += KEY_W;
	if (keycode == 97)
		data->key_press += KEY_A;
	if (keycode == 115)
		data->key_press += KEY_S;
	if (keycode == 100)
		data->key_press += KEY_D;
	if (keycode == 65307)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_hook_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->key_press -= KEY_W;
	if (keycode == 97)
		data->key_press -= KEY_A;
	if (keycode == 115)
		data->key_press -= KEY_S;
	if (keycode == 100)
		data->key_press -= KEY_D;
	return (0);
}

int	mouse_move_hook(int x, int y, t_data *data)
{
	(void) y;
	data->game.player.dir = rotate_vector((x - data->width / 2) * 0.001, data->game.player.dir);
	mlx_mouse_move(data->mlx, data->win, data->width / 2, data->height / 2);
	return (0);
}

int	button_hook(int button, int x, int y, t_data *data)
{
	(void) x;
	(void) y;
	if (button == 4)
		data->fov++;
	else if (button == 5)
		data->fov--;
	if (button == 4 || button == 5)
	{
		free(data->game.text.text);
		data->game.text.text = ft_itoa((int)data->fov);

	}
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->key_press & KEY_W)
	{
		data->game.player.pos.x += 0.01 * data->game.player.dir.x;
		data->game.player.pos.y += 0.01 * data->game.player.dir.y;
	}
	if (data->key_press & KEY_S)
	{
		data->game.player.pos.x -= 0.01 * data->game.player.dir.x;
		data->game.player.pos.y -= 0.01 * data->game.player.dir.y;
	}
	if (data->key_press & KEY_A)
	{
		data->game.player.pos.x += 0.01 * data->game.player.dir.y;
		data->game.player.pos.y += 0.01 * -data->game.player.dir.x;
	}
	if (data->key_press & KEY_D)
	{
		data->game.player.pos.x -= 0.01 * data->game.player.dir.y;
		data->game.player.pos.y -= 0.01 * -data->game.player.dir.x;
	}

	draw_sky_ground(data, 0xace0e8, 0x254a08);
	draw_map(data);
	draw_text(data, &data->game.text);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
