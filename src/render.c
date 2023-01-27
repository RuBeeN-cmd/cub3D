#include "../include/cub3D.h"

void	draw_dot(t_data *data, int size, int pos_x, int pos_y, int color)
{
	for (int i = 0; i < data->img.width; i++)
		if (i >= pos_x - size / 2 && i <= pos_x + size / 2)
			for (int j = 0; j < data->img.height; j++)
				if (j >= pos_y - size / 2 && j <= pos_y + size / 2)
					if (j * data->img.width + i > 0 && j * data->img.width + i < data->img.height * data->img.width)
						((int*) data->img.buf)[j * data->img.width + i] = color;
}

void	draw_background(t_data *data, int color)
{
	int		x;
	int		y;
	char	*dst;

	dst = data->img.buf;
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			*(unsigned int*) dst = color;
			dst += data->img.pixel_bits / 8;
			x++;
		}
		y++;
	}
}

void	draw_grid(t_data *data, int size, int color)
{
	int		i;
	int		j;
	int		pix;

	j = 0;
	while (j < data->game.map.height)
	{
		i = 0;
		while (i < data->img.width)
		{
			pix = (j - data->game.player.pos.y) * size + data->img.height / 2;
			if (pix > 0 && pix < data->img.height)
				((int*) data->img.buf)[pix * data->img.width + i] = color;
			i++;
		}
		j++;
	}
	i = 0;
	while (i < data->game.map.width)
	{
		j = 0;
		while (j < data->img.height)
		{
			pix = (i - data->game.player.pos.x) * size + data->img.width / 2;
			if (pix > 0 && pix < data->img.width)
				((int*) data->img.buf)[j * data->img.width + pix] = color;
			j++;
		}
		i++;
	}
}

t_point	get_dist(t_ray ray)
{
	t_point	dist;
	
	if (ray.vector.x < 0)
		dist.x = -1 / ray.vector.x * (ray.start.x - (int) ray.start.x);
	else
	{
		if (ray.vector.x)
			dist.x = 1 / ray.vector.x * (1 - ray.start.x + (int) ray.start.x);
		else
			dist.x = 1e30;
	}
	if (ray.vector.y < 0)
		dist.y = -1 / ray.vector.y * (ray.start.y - (int) ray.start.y);
	else
	{
		if (ray.vector.y)
			dist.y = 1 / ray.vector.y * (1 - ray.start.y + (int) ray.start.y);
		else
			dist.x = 1e30;
	}
	return (dist);
}

t_point	get_delta(t_ray ray)
{
	t_point	delta;

	if (ray.vector.x)
		delta.x = fabs(1 / ray.vector.x);
	else
		delta.x = 1e30;
	if (ray.vector.y)
		delta.y = fabs(1 / ray.vector.y);
	else
		delta.y = 1e30;
	return (delta);
}

t_intersect	*get_ray_data(t_data *data, t_ray ray, float render_dist)
{
	t_intersect *intersect;
	t_point		dist;
	t_point		delta;
	int			hit;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	int			side;

	if (ray.vector.x < 0)
	{
		stepX = -1;
		dist.x = -(ray.start.x - (int) ray.start.x) / ray.vector.x;
	}
	else
	{
		stepX = 1;
		if (ray.vector.x)
			dist.x = ((int) ray.start.x + 1.0 - ray.start.x) / ray.vector.x;
		else
			dist.y = 1e30;
	}
	if (ray.vector.y < 0)
	{
		stepY = -1;
		dist.y = -(ray.start.y - (int) ray.start.y) / ray.vector.y;
	}
	else
	{
		stepY = 1;
		if (ray.vector.y)
			dist.y = ((int) ray.start.y + 1.0 - ray.start.y) / ray.vector.y;
		else
			dist.y = 1e30;
	}
	delta = get_delta(ray);
	hit = 0;
	mapX = (int) ray.start.x;
	mapY = (int) ray.start.y;
	while (!hit && dist.x - delta.x < render_dist && dist.y - delta.y < render_dist)
	{
		if (dist.x < dist.y)
		{
			dist.x += delta.x;
			mapX += stepX;
			side = 0;
		}
		else
		{
			dist.y += delta.y;
			mapY += stepY;
			side = 1;
		}
		if (mapX >= 0 && mapX < data->game.map.width)
			if (mapY >= 0 && mapY < data->game.map.height)
				if (data->game.map.map[mapY][mapX])
					hit = 1;
	}
	if (hit)
	{
		intersect = malloc(sizeof(t_intersect));
		if (side == 0)
			intersect->dist = dist.x - delta.x;
		else
			intersect->dist = dist.y - delta.y;
		return (intersect);
	}
	return (NULL);
}

//void	draw_map(t_data *data)
//{
//	int	grid_size = 50;


//	int i;
//	t_ray ray;
//	double a;
//	t_intersect *intersect;

//	draw_background(data, 0);
//	draw_grid(data, grid_size, 0x7f7f7f);
//	draw_dot(data, 5, data->img.width / 2, data->img.height / 2, 0xff00000);
//	a = atan2(data->game.player.dir.y, data->game.player.dir.x) - data->fov * PI / 360.0;
//	i = 0;
//	while (i < data->img.width)
//	{
//		ray.start = data->game.player.pos;
//		ray.vector.x = cos(a);
//		ray.vector.y = sin(a);
//		a += data->fov / (data->img.width - 1) * PI / 180.0;


//		draw_dot(data, 1,
//		data->img.width / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.x,
//		data->img.height / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.y,
//		0x00ff00);


//		intersect = get_ray_data(data, ray, 3);
//		if (intersect)
//		{
//			draw_dot(data, 2,
//			data->img.width / 2 + intersect->dist * ray.vector.x * grid_size,
//			data->img.height / 2 + intersect->dist * ray.vector.y * grid_size,
//			0xffff00);
//		}
//		//print_list(intersect);
//		//free_intersect(intersect);
//		if (i == 0)
//		{
//			if (intersect)
//			{
//				draw_dot(data, 6,
//				data->img.width / 2 + intersect->dist * ray.vector.x * grid_size,
//				data->img.height / 2 + intersect->dist * ray.vector.y * grid_size,
//				0x00ffff);
//			}
//			draw_dot(data, 6,
//			data->img.width / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.x,
//			data->img.height / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.y,
//			0x00ffff);
//		}
//		if (intersect)
//			free(intersect);
//		i++;
//	}
//	draw_dot(data, 4, data->img.width / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * data->game.player.dir.x,
//		data->img.height / 2 + (get_min(data->img.width, data->img.height) - 100) / 2 * data->game.player.dir.y, 0x0000ff);
//}


void	draw_vline(t_data *data, int x, int y_start, int y_end, int color)
{
	while (y_start < y_end)
	{
		((int*) data->img.buf)[y_start * data->img.width + x] = color;
		y_start++;
		if (y_start >= data->img.height || y_start < 0)
			return ;
	}
}

void	draw_map(t_data *data)
{
	int			i;
	t_ray		ray;
	double		a;
	t_intersect	*intersect;

	a = atan2(data->game.player.dir.y, data->game.player.dir.x) - data->fov * PI / 360.0;
	i = 0;
	while (i < data->img.width)
	{
		ray.start = data->game.player.pos;
		ray.vector.x = cos(a);
		ray.vector.y = sin(a);
		a += data->fov / (data->img.width - 1) * PI / 180.0;
		intersect = get_ray_data(data, ray, 3);
		if (intersect)
		{
			draw_vline(data, i, data->img.height / 2 - 1 / intersect->dist * 200, data->img.height / 2 + 1 / intersect->dist * 200, 0xffffff);
			free(intersect);
		}
		i++;
	}
}