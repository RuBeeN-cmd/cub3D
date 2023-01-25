#include "cub3D.h"

void	realloc_str(char **str_ptr, int size_to_add)
{
	char	*str;
	int		len;

	len = ft_strlen(*str_ptr);
	str = malloc(sizeof(char) * (len + size_to_add + 1));
	ft_strcpy(str, *str_ptr);
	free(*str_ptr);
	*str_ptr = str;
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
	dest[i] = 0;
	return dest;
}