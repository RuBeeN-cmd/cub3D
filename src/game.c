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

// only 0, 1, N, S, E, W
// only one N, S, E, W
int		check_error(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != '0' && buf[i] != '1' && buf[i] != 'N' && buf[i] != 'S' && buf[i] != 'E' && buf[i] != 'W')
			return (1);
		i++;
		while (buf[i] == '\n')
			i++;
	}
	return (0);
}

void	init_game(t_game *game, char *buf)
{
	if (check_error(buf))
	{
		free(buf);
		exit(1);
	}
	(void) game;
}

void	create_game(t_game *game, int argc, char *argv[])
{
	char	*buf;

	if (argc != 1)
		exit(1);
	if (check_extension(*argv, "cub"))
		exit(1);
	buf = read_file(*argv);
	init_game(game, buf);
	free(buf);
}
