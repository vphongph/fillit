#include "fillit.h"
#include <stdio.h>

t_coords find_next_block(char *tetro, int last_block)
{
	while (tetro[i] == '.' || tetro[i] == '\n')
	{
		if (tetro[i] == '.')
			new_x++;
		if (tetro[i] == '\n')
			new_x = x;
		i++;
	}
}

int		try_tetro_at(t_map *map, char *tetro, t_coords coords)
{
	int		i;
	int 	j;
	int		new_x;

	i = 0;
	j = x + (map->size + 1)* y;
	new_x = x;


	while (tetro[i])
	{
		while (tetro[i] == '.' || tetro[i] == '\n')
		{
			if (tetro[i] == '\n')
				j += map->size - 1;
			else
				j++;
			i++;
		}
		if (!tetro[i] || map->map[j] != '.')
			return (-1);
		map->map[j] = tetro[i];
		j++;
		i++;
	}
	return (0);
}

char 	*create_map(int size)
{
	char	*map;
	int		i;
	int		j;

	if (!(map = (char *)malloc(sizeof(char) * (size * (size + 1)))))
	{
		ft_putendl("There was an issue while allocating memory");
		exit(0);
	}
	i = 0;
	j = 0;
	while (i < (size + 1) * size)
	{
		if (j == size)
		{
			j = -1;
			map[i++] = '\n';
		}
		else
			map[i++] = '.';
		j++;
	}
	map[i - 1] = '\0';
	return (map);
}

int		main(int ac, char **av)
{
	t_map *map_struct;
	char **tetros;
	int	 tetros_count;
	t_coords	coords;

	tetros_count = 5;
	tetros = (char **)malloc(sizeof(char *) * tetros_count);
	tetros[0] = "AA\nAA\0";
	tetros[1] = "B.\nB.\nBB\0";
	tetros[2] = "C\nC\nC\nC\0";
	tetros[3] = "DD\nDD\0";
	tetros[4] = "EE.\n.EE\0";
	map_struct = (t_map *)malloc(sizeof(t_map *));
	map_struct->size = ft_floor_sqrt(tetros_count * 4);
	printf("%d\n", map_struct->size);
	map_struct->map = create_map(map_struct->size);
	coords.x = 3;
	coords.y = 3;
	(void)try_tetro_at(map_struct, tetros[0], 3, 3);
	ft_putendl(map_struct->map);
	return (0);
}