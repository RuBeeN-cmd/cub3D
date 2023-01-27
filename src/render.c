#include "../include/cub3D.h"

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

//float	get_delta(t_ray ray)
//{
//	float	adj;
//	t_point	delta;
	
//	if (ray.vector.x)
//		delta.x = abs(1 / ray.vector.x);
//	if (ray.vector.y)
//		delta.y = abs(1 / ray.vector.y);
//	if (ray.vector.x && ray.vector.y)
//		return (get_min(delta.x, delta.y));
//	if (ray.vector.x)
//		return (delta.x);
//	return (delta.y);
//}

//t_intersect	get_ray_data(t_data *data, t_ray ray, float render_dist)
//{
//	t_intersect intersect;

//	(void) data;
//	(void) render_dist;
//	intersect->dist = get_dist(ray);
//	intersect->wall_height = 0;
//	return (intersect);
//}


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

void	draw_dot(t_data *data, int size, int pos_x, int pos_y, int color)
{
	for (int i = 0; i < data->img.width; i++)
		if (i >= pos_x - size / 2 && i <= pos_x + size / 2)
			for (int j = 0; j < data->img.height; j++)
				if (j >= pos_y - size / 2 && j <= pos_y + size / 2)
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

void	draw_map(t_data *data)
{
	int	grid_size = 50;


	int i;
	t_ray ray;
	double a;
	//t_intersect	*intersect;

	draw_background(data, 0);
	draw_grid(data, grid_size, 0x7f7f7f);
	draw_dot(data, 5, data->img.width / 2, data->img.height / 2, 0xff00000);
	a = atan2(data->game.player.dir.y, data->game.player.dir.x) + data->fov * PI / 360.0;
	i = 0;
	while (i < data->img.width)
	{
		ray.start = data->game.player.pos;
		ray.vector.x = cos(a);
		ray.vector.y = sin(a);


		draw_dot(data, 1,
		data->img.width / 2 - (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.x,
		data->img.height / 2 - (get_min(data->img.width, data->img.height) - 100) / 2 * ray.vector.y,
		0x00ff00);



		a -= data->fov / (data->width - 1) * PI / 180.0;
		//intersect = get_ray_data(data, ray, 3);
		//print_list(intersect);
		//free_intersect(intersect);
		i++;
	}
	draw_dot(data, 4, data->img.width / 2 - (get_min(data->img.width, data->img.height) - 100) / 2 * data->game.player.dir.x,
		data->img.height / 2 - (get_min(data->img.width, data->img.height) - 100) / 2 * data->game.player.dir.y, 0x0000ff);
}

