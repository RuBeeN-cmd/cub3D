#include "cub3D.h"

void	create_new_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, data->width, data->height);
	data->img.buf = mlx_get_data_addr(data->img.img, &data->img.pixel_bits, &data->img.line_len, &data->img.endian);
	data->img.width = data->width;
	data->img.height = data->height;
}

void	destroy_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
}