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

int		check_error(char *buf)
{
	int	i;
	int	nb_player;

	nb_player = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'E' || buf[i] == 'W')
			nb_player++;
		else if (buf[i] != '0' && buf[i] != '1')
			return (1);
		if (nb_player > 1)
			return (1);
		i++;
		while (buf[i] == '\n')
			i++;
	}
	return (nb_player != 1);
}

//int	get_row_nb(char *buf)
//{
//	int	row_nb;
	
//	row_nb = 0;
//	while (buf[i] == '\n')
//		i++;
//	while (buf[i])
//	{
//		if (buf[i] == '\n')
//			row_nb++;
//		while (buf[i] == '\n')
//			i++;
//	}
//}

//void	parse_map(t_game *game, char *buf)
//{
//	int	row_nb;
//	int	i;

//	i = 0;
//	row_nb = get_row_nb(buf);
//	while (buf[i] == '\n')
//		i++;
//	while (buf[i])
//	{

//	}
//}

//void	init_game(t_game *game, char *buf)
//{
//	if (check_error(buf))
//	{
//		free(buf);
//		exit(1);
//	}
//	parse_map(game, buf);
//}

void	create_game(t_game *game, int argc, char *argv[])
{
	char	*buf;

	if (argc != 1)
		exit(1);
	if (check_extension(*argv, "cub"))
		exit(1);
	buf = read_file(*argv);
	(void) game;
	//init_game(game, buf);
	free(buf);
}
