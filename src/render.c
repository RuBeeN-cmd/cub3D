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

int	average_color(int color1, int color2, float f)
{
	int	new_color = 0;
	int	tmp;
	int i = 0;

	if (f < 0 || f > 1)
		return (0);
	while (i < 3)
	{
 		tmp = ((color1 >> 8 * i) & 0xff) * f + ((color2 >> 8 * i) & 0xff) * (1.0 - f);
		if (tmp > 255)
			tmp = 0;
		new_color += tmp << (i * 8);
		i++;
	}
	return (new_color);
}

typedef enum s_color {
	RED, GREEN, BLUE, YELLOW
}			t_color;

int		color_to_int(t_color color)
{
	if (color == RED)
		return (0xff0000);
	else if (color == GREEN)
		return (0x00ff00);
	else if (color == BLUE)
		return (0x0000ff);
	return (0xffff00);
}

void	draw_wall(t_data *data, int x, t_intersect *intersect)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	max_height = 4;
	int	fog_color = 0;
	int dist_max = 20;
	t_color	color;

	color = intersect->color;
	lineHeight = ((float) data->img.height) / intersect->dist;
	drawEnd = lineHeight / 2 + data->img.height / 2;
	drawStart = drawEnd - lineHeight * intersect->wall_height / max_height;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= data->img.height)
		drawEnd = data->img.height - 1;
	draw_vline(data, x, drawStart, drawEnd, average_color(fog_color, color_to_int(color), intersect->dist / dist_max));
}

float	degree_to_radian(float degree)
{
	return (degree * PI / 180);
}

void	free_intersect(t_intersect **intersect)
{
	if (!(*intersect)->back)
	{
		free(*intersect);
		*intersect = NULL;
	}
	else
	{
		*intersect = (*intersect)->back;
		free((*intersect)->next);
		(*intersect)->next = NULL;
	}
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
		intersect = get_ray_data(data, ray);
		while (intersect)
		{
			draw_wall(data, i, intersect);
			free_intersect(&intersect);
		}
		ray = increment_ray(data, delta, ray, &proj);
		i++;
	}
}