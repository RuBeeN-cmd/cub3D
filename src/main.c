#include "cub3D.h"

int main(int argc, char *argv[])
{
	t_data	data;
	init_data(&data, argc - 1, argv + 1);
	mlx_loop(data.mlx);
	destroy_data(data);
	return (0);
}