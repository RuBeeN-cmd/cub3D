#include "../include/cub3D.h"
#include <math.h>
/*
typedef struct	s_intersect
{
	float		dist;
	float		wall_height;
	struct s_intersect	*next;
}				t_intersect;

t_intersect *get_ray_data(t_data *data, t_ray ray, float render_dist)
{
	float	adj_x;
	float	adj_y;
	float	dist_x;
	float	dist_y;
	t_ray	new_ray;
	t_intersect	*intersect;

	if (ray.vector.x)
	{
		adj_x = ray.start.x - (int)ray.start.x + 1;
		dist_x = (1/ray.vector.x) * adj_x;
	}
	if (ray.vector.y)
	{
		adj_y = ray.start.y - (int)ray.start.y + 1;
		dist_y = (1/ray.vector.y) * adj_y;
	}
	if (dist_x < dist_y)
	{
		new_ray.start.x = ray.start.x + dist_x * ray.vector.x;
		new_ray.start.y = ray.start.y + dist_x * ray.vector.y;
	}
	else
	{
		new_ray.start.x = ray.start.x + dist_y * ray.vector.x; 
		new_ray.start.y = ray.start.y + dist_y * ray.vector.y;
	}
	new_ray.vector = ray.vector;
	intersect = get_ray_data(data, new_ray, render_dist);
	if (data->game.map[(int)new_ray.start.y][(int)new_ray.start.x] > 0)
	intersect.next = 
}

void	draw_map(t_data *data)
{
	int i;
	t_ray ray;
	double a;

	a = (PI - FOV) / 2.0;
	while (i < data->width)
	{
		ray.start = data->game.player.pos;
		ray.vector.x = -cos(a);
		ray.vector.y = sin(a);
		a = a + FOV / (data->width - 1);
		
		i++;
	}
}
*/

