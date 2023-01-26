#include "../include/cub3D.h"
#include <stdio.h>

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
		if (text->text[i] >= 97 && text->text[i] <= 122)
		{
			buf = (int*)text->sprite[0].buf; 
			text_index = (text->text[i] - 97);
		}
		else if (text->text[i] >= 65 && text->text[i] <= 90)
		{
			buf = (int*)text->sprite[1].buf; 
			text_index = (text->text[i] - 65);
		}
		else
		{
			i++;
			continue;
		}
		y = 0;
		while (y < 16)
		{
				x_min = text_index * 16;
				x_max = (text_index + 1) * 16;
				while (x_min < x_max)
				{
					if (buf[y * text->sprite->width + x_min] != COLOR_MASK)
						((int*)data->img.buf)[(text->pos_y + y) * data->img.width + text->pos_x + i * 16 + x_min % 16] = buf[y * text->sprite->width + x_min];
					x_min++;
				}
				y++;
		}
		i++;
	}
} 
