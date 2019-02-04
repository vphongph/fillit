#include "fillit.h"

int		ft_floor_sqrt(int x)
{
	int	res;
	int i;

	if (x <= 0 || x == 1)
		return (x);
	res = 0;
	i = 0;
	while (res < x)
	{
		i++;
		res = i * i;
	}
	return (i);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putendl(char *str)
{
	int	length;

	length = ft_strlen(str);
	write(1, str, length);
	write(1, "\n", 1);
}