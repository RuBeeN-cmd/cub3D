#include "../include/cub3D.h"
/*
float	get_dist(t_ray ray)
{
	float	adj;
	t_point	dist;
	
	if (ray.vector.x)
	{
		adj = ray.start.x - (int) ray.start.x + 1;
		dist.x = 1 / ray.vector.x * adj;
	}
	if (ray.vector.y)
	{
		adj = ray.start.y - (int) ray.start.y + 1;
		dist.y = 1 / ray.vector.y * adj;
	}
	if (ray.vector.x && ray.vector.y)
		return (get_min(dist.x, dist.y));
	if (ray.vector.x)
		return (dist.x);
	return (dist.y);
}

//t_intersect *get_ray_data(t_data *data, t_ray ray, float render_dist)
//{
//	float dist;
//	t_ray new_ray;
//	t_intersect *intersect_lst;
//	t_intersect *intersect;
//	float wall_height;

//	// check if the ray is within the map boundaries
//	if ((int)ray.start.y < 0 || (int)ray.start.y > 100 || (int)ray.start.x < 0 || (int)ray.start.x > 100)
//		return (NULL);

//	// calculate the distance to the next wall
//	dist = get_dist(ray);

//	// base case for recursion: if distance traveled exceeds render distance, return NULL
//	if (dist > render_dist)
//		return (NULL);

//	// create a new ray with the distance
//	new_ray.start.x = ray.start.x + dist * ray.vector.x;
//	new_ray.start.y = ray.start.y + dist * ray.vector.y;
//	new_ray.vector = ray.vector;

//	// recursively call the function with the new ray and updated render distance
//	intersect_lst = get_ray_data(data, new_ray, render_dist - dist);
//	wall_height = data->game.map.map[(int)ray.start.y][(int)ray.start.x];

//	// if there is a wall at the current position, create a new intersection node
//	if (wall_height > 0)
//	{
//		intersect = (t_intersect *)malloc(sizeof(t_intersect));
//		intersect->wall_height = wall_height;
//		intersect->dist = dist;
//		intersect->next = intersect_lst;
//		intersect_lst = intersect;
//	}
//	return (intersect_lst);
//}

t_intersect	*get_ray_data(t_data *data, t_ray ray, float render_dist)
{
	float	dist;
	float	delta;
	t_point	new_pos;

	dist = get_dist(ray);
	delta = dist;
	new_pos = ray.start;
	while (dist < render_dist)
	{
		new_pos.x += delta * ray.vector.x;
		new_pos.y += delta * ray.vector.y;
		dist += 
	}
	
}


void	print_list(t_intersect *intersect)
{
	while (intersect)
	{
		printf("Intersection:\n\tDist:\n\t\t%f\n\tWall_Height:\n\t\t%f\n\n", intersect->dist, intersect->wall_height);
		intersect = intersect->next;
	}
}

void	free_intersect(t_intersect *intersect)
{
	if (intersect)
	{
		free_intersect(intersect->next);
		free(intersect);
	}
}

void	draw_map(t_data *data)
{
	int i;
	t_ray ray;
	double a;
	t_intersect	*intersect;

	a = (PI - FOV) / 2.0;
	i = 0;
	while (i < data->width && i == 0)
	{
		ray.start = data->game.player.pos;
		ray.vector.x = -cos(a);
		ray.vector.y = sin(a);
		a = a + FOV / (data->width - 1);
		intersect = get_ray_data(data, ray, 3);
		//write(1, "z", 1);
		print_list(intersect);
		free_intersect(intersect);
		i++;
	}
}
*/

