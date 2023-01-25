#include "cub3D.h"

void	draw_sky_ground(t_data *data, int sky_color, int ground_color)
{
	int		x;
	int		y;
	int		crt_color;
	char	*dst;

	dst = data->img.buf;
	crt_color = sky_color;
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			*(unsigned int*) dst = crt_color;
			dst += data->img.pixel_bits / 8;
			x++;
		}
		if (y == data->img.height / 2)
			crt_color = ground_color;
		y++;
	}
}