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

static int isNum(char c)
{
	return (c >= '0' && c <= '9');
}

static int set_case(t_text *text, t_img *buf, int i)
{
		if (isLowerCase(text->text[i]))
		{
			*buf = text->sprite[0]; 
			return (text->text[i] - 97);
		}
		else if (isUpperCase(text->text[i]))
		{
			*buf = text->sprite[1]; 
			return (text->text[i] - 65);
		}
		else if(isNum(text->text[i]))
		{
			*buf = text->sprite[2];
			return (text->text[i] - 48);
		}
		return (-1);
}


void	draw_text(t_data *data, t_text *text)
{
	int x_min = 0;
	int x_max = 0;
	int y;
	int i = 0;
	int text_index = 0;
	t_img sprite;

	while(text->text[i])
	{

		text_index = set_case(text, &sprite, i);
		if (text_index == -1)
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
				if (((int*)sprite.buf)[y * sprite.width + x_min] != COLOR_MASK)
					((int*)data->img.buf)[(text->pos_y + y) * data->img.width +
						text->pos_x + i * FONT_SIZE + x_min % FONT_SIZE] =
						((int*)sprite.buf)[y * sprite.width + x_min];
				x_min++;
			}
			y++;
		}
		i++;
	}
} 
