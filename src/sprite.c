#include "cub3D.h"

void	draw_sprite(t_data *data, int pos_y, int pos_x, t_img sprite)
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