#include "cub3D.h"

t_point	rotate_vector(float angle, t_point vector)
{
	t_point	new;

	new.x = cos(angle) * vector.x - sin(angle) * vector.y;
	new.y = sin(angle) * vector.x + cos(angle) * vector.y;
	return (new);
}

t_point	add_vector(t_point v1, t_point v2)
{
	t_point	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	return (new);
}

t_point	sub_vector(t_point v1, t_point v2)
{
	t_point	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	return (new);
}

float	dot_vector(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_point	mult_vector(t_point vector, float f)
{
	t_point	new;

	new.x = vector.x * f;
	new.y = vector.y * f;
	return (new);
}