#include "../include/cub3D.h"

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

void	draw_wall(t_data *data, int x, t_intersect *intersect)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	max_height = 4;
	
	lineHeight = ((float) data->img.height) / intersect->dist;
	drawEnd = lineHeight / 2 + data->img.height / 2;
	drawStart = drawEnd - lineHeight * intersect->wall_height / max_height;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= data->img.height)
		drawEnd = data->img.height - 1;
	draw_vline(data, x, drawStart, drawEnd, 0xffffff);
}

float	degree_to_radian(float degree)
{
	return (degree * PI / 180);
}

void	draw_map(t_data *data)
{
	int			i;
	float		delta;
	t_ray		ray;
	t_intersect	*intersect;
	t_point		proj;

	delta = tan(degree_to_radian(data->fov / 2.0));
	ray = init_first_ray(data, delta, &proj);
	delta /= data->img.width / 2;
	i = 0;
	while (i < data->img.width)
	{
		intersect = get_ray_data(data, ray, 20);
		// while (intersect && intersect->back)
		// 	intersect = intersect->back;
		while (intersect && intersect->back)
		{
			draw_wall(data, i, intersect);
			intersect = intersect->back;
			free(intersect->next);
		}
		if (intersect)
		{
			draw_wall(data, i, intersect);
			free(intersect);
		}
		ray = increment_ray(data, delta, ray, &proj);
		i++;
	}
}