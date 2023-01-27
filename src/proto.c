#include "../include/cub3D.h"
#include <stdio.h>


static int isLowerCase(char c)
{
	return (c >= 'a' && c <= 'z');
}

static int isUpperCase(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static int set_case(t_text *text, int **buf, int i)
{
		if (isLowerCase(text->text[i]))
		{
			*buf = (int*)text->sprite[0].buf; 
			return (text->text[i] - 97);
		}
		else if (isUpperCase(text->text[i]))
		{
			*buf = (int*)text->sprite[1].buf; 
			return (text->text[i] - 65);
		}
		return (0);
}

void	draw_text(t_data *data, t_text *text)
{
	int y;
	int x_min = 0;
	int x_max = 0;
	int i = 0;
	int text_index = 0;
	int *buf;

	while(text->text[i])
	{

		text_index = set_case(text, &buf, i);
		if (!text_index)
		{
			i++;
			continue;
		}
		y = 0;
		while (y < FONT_SIZE)
		{
				x_min = text_index * FONT_SIZE;
				x_max = (text_index + 1) * FONT_SIZE;
				while (x_min < x_max)
				{
					if (buf[y * text->sprite->width + x_min] != COLOR_MASK)
						((int*)data->img.buf)[(text->pos_y + y) * data->img.width + text->pos_x + i * FONT_SIZE + x_min % FONT_SIZE] = buf[y * text->sprite->width + x_min];
					x_min++;
				}
				y++;
		}
		i++;
	}
} 
