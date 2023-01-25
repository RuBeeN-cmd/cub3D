#include "cub3D.h"

static int	check_extension(char *str, char *ext)
{
	int	i;

	if (!str || !ext)
		return (1);
	while (*str)
	{
		while (*(str + 1) && *str != '.')
			str++;
		str++;
		if (!*str)
			return (1);
		i = 0;
		while (str[i] && str[i] == ext[i])
			i++;
		if (!ext[i])
			return (0);
		else if (!str[i])
			return (1);
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char *ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return dest;
}

void	realloc_str(char **str_ptr, int size_to_add)
{
	char	*str;
	int		len;

	len = ft_strlen(*str_ptr);
	str = malloc(sizeof(char) * (len + size_to_add + 1));
	printf("%d\n", (len + size_to_add + 1));
	ft_strcpy(str, *str_ptr);
	free(*str_ptr);
	*str_ptr = str;
}

char	*read_file(int fd)
{
	char	*str;
	char	buf;
	int		i;
	int		malloc_size;

	str = NULL;
	malloc_size = 16;
	i = 0;
	while (read(fd, &buf, 1))
	{
		if (i % malloc_size == 0)
			realloc_str(&str, malloc_size);
		str[i] = buf;
		i++;
		if (i % malloc_size == 0)
			str[i] = 0;
	}
	str[i] = 0;
	if (i % malloc_size + 1)
		realloc_str(&str, -((i + 1) % malloc_size - 2));
	return (str);
}

void	create_game(t_game *game, int argc, char *argv[])
{
	int		fd;
	char	*buf;

	if (argc != 1)
		exit(1);
	if (check_extension(*argv, "cub"))
		exit(1);
	fd = open(*argv, O_RDONLY);
	if (fd == -1)
		exit(1);
	//buf = read_file(fd);
	//printf("%s\n", buf);
	(void) game, (void) buf;
	close(fd);
}
