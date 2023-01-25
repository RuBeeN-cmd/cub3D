#include "cub3D.h"

char	*read_file(char *path)
{
	int		fd;
	int		malloc_size;
	char	*str;
	char	buf;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	str = NULL;
	malloc_size = 16;
	i = 0;
	while (read(fd, &buf, 1))
	{
		if (i % malloc_size == 0)
			realloc_str(&str, malloc_size);
		str[i] = buf;
		if (++i % malloc_size == 0)
			str[i] = 0;
	}
	close(fd);
	str[i] = 0;
	if (i % malloc_size)
		realloc_str(&str, 0);
	return (str);
}