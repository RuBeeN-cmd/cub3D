#include "cub3D.h"

t_ray	init_first_ray(t_data *data, float delta, t_point *proj)
{
	t_ray		ray;

	proj->x = data->game.player.pos.x + data->game.player.dir.x + data->game.player.dir.y * delta;
	proj->y = data->game.player.pos.y + data->game.player.dir.y - data->game.player.dir.x * delta;
	ray.start.x = data->game.player.pos.x;
	ray.start.y = data->game.player.pos.y;
	ray.vector = sub_vector(*proj, data->game.player.pos);
	return (ray);
}

t_ray	increment_ray(t_data *data, float delta, t_ray ray, t_point *proj)
{
	proj->x -= delta * data->game.player.dir.y;
	proj->y += delta * data->game.player.dir.x;
	ray.vector.x = proj->x - data->game.player.pos.x;
	ray.vector.y = proj->y - data->game.player.pos.y;
	return (ray);
}

void	get_delta(t_ray ray, t_point *delta)
{
	if (ray.vector.x)
		delta->x = fabs(1 / ray.vector.x);
	else
		delta->x = 1e30;
	if (ray.vector.y)
		delta->y = fabs(1 / ray.vector.y);
	else
		delta->y = 1e30;
}

void	get_dist(t_ray ray, t_intpoint *step, t_point *dist)
{
	step->x = 1;
	if (ray.vector.x < 0)
		step->x = -1;
	step->y = 1;
	if (ray.vector.y < 0)
		step->y = -1;
	dist->x = 1e30;
	dist->y = 1e30;
	if (ray.vector.x < 0)
		dist->x = -(ray.start.x - (int) ray.start.x);
	else if (ray.vector.x > 0)
		dist->x = ((int) ray.start.x - ray.start.x + 1);
	if (ray.vector.y < 0)
		dist->y = -(ray.start.y - (int) ray.start.y);
	else if (ray.vector.y > 0)
		dist->y = ((int) ray.start.y - ray.start.y + 1);
	dist->x /= ray.vector.x;
	dist->y /= ray.vector.y;
}

t_intersect	*get_intersect(t_data *data, t_point dist, t_point delta, t_intpoint step, t_intpoint map_index)
{
	t_intersect *intersect;
	int			mapX2 = 0;
	int			mapY2 = 0;
	int			side;

	intersect = NULL;
	while (map_index.x >= 0 && map_index.x < data->game.map.width
		&& map_index.y >= 0 && map_index.y < data->game.map.height)
	{
		if (dist.x < dist.y)
		{
			dist.x += delta.x;
			map_index.x += step.x;
			side = 0;
		}
		else
		{
			dist.y += delta.y;
			map_index.y += step.x;
			side = 1;
		}
		if (side)
		{
			mapY2 = map_index.y - step.x;
			mapX2 = map_index.x;
		}
		else
		{
			mapX2 = map_index.x - step.x;
			mapY2 = map_index.y;
		}
		for (int i = 0; i < 2; i++)
		{
			if (mapX2 >= 0 && mapX2 < data->game.map.width)
			{
				if (mapY2 >= 0 && mapY2 < data->game.map.height)
				{
					if (data->game.map.map[mapY2][mapX2])
					{
						if (!intersect)
						{
							intersect = malloc(sizeof(t_intersect));
							intersect->back = NULL;
						}
						else
						{
							intersect->next = malloc(sizeof(t_intersect));
							intersect->next->back = intersect;
							intersect = intersect->next;
						}
						intersect->next = NULL;
						intersect->wall_height = data->game.map.map[mapY2][mapX2];
						intersect->color = side << 1;
						if (side)
							intersect->color += (step.x > 0);
						else
							intersect->color += (step.x > 0);

						if (side == 0)
							intersect->dist = dist.x - delta.x;
						else
							intersect->dist = dist.y - delta.y;
					}
				}
			}
			if (side)
				mapY2 += step.x;
			else
				mapX2 += step.x;
		}
	}
	return (intersect);
}

t_intersect	*get_ray_data(t_data *data, t_ray ray)
{
	t_intersect *intersect;
	t_intpoint	step;
	t_intpoint	map_index;
	t_point		dist;
	t_point		delta;

	get_dist(ray, &step, &dist);
	get_delta(ray, &delta);
	map_index.x = (int) ray.start.x;
	map_index.y = (int) ray.start.y;
	intersect = get_intersect(data, dist, delta, step, map_index);
	return (intersect);
}