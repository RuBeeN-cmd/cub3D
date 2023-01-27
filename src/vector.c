#include "cub3D.h"

t_point	rotate_vector(float angle, t_point vector)
{
	t_point	new;

	new.x = cos(angle) * vector.x - sin(angle) * vector.y;
	new.y = sin(angle) * vector.x + cos(angle) * vector.y;
	return (new);
}
