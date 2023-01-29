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
	int			mapX;
	int			mapY;
	int			mapX2;
	int			mapY2;
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
	mapX = (int) ray.start.x;
	mapY = (int) ray.start.y;
	intersect = NULL;
	while (dist.x - delta.x < render_dist && dist.y - delta.y < render_dist)
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
		if (side)
		{
			mapY2 = mapY - stepY;
			mapX2 = mapX;
		}
		else
		{
			mapX2 = mapX - stepX;
			mapY2 = mapY;
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
						if (side == 0)
							intersect->dist = dist.x - delta.x;
						else
							intersect->dist = dist.y - delta.y;
					}
				}
			}
			if (side)
				mapY2 += stepY;
			else
				mapX2 += stepX;
		}
	}
	return (intersect);
}