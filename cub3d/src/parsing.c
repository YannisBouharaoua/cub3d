/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:28:19 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 16:30:25 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

static void	print_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	printf("Map %dx%d, player %c at (%d,%d)\n",
		map->width, map->height, map->player_dir,
		map->player_x, map->player_y);
	y = 0;
	while (map->grid[y])
	{
		printf("%s\n", map->grid[y]);
		y++;
	}
}

int not_directory(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int parsing(int ac, char **av)
{
	char	*path_map;
	t_cub	cub;

	if (ac < 2)
		return (1);
	path_map = av[1];
	if (not_directory(path_map))
	{
		if (good_map(path_map))
		{
			printf("GoodMap\n");
			init_map(&cub.map, path_map);
			print_map(&cub.map);
			return (0);
		}
		printf("BadMap Format\n");
		printf("Debug: forcing init_map/print_map despite bad format\n");
		init_map(&cub.map, path_map);
		print_map(&cub.map);
		return (1);
	}
	printf("Is a Directory\n");
	return (1);
}
