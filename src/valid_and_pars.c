/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_and_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:42:00 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/26 18:42:00 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		set_player_pos(t_map *map, int texture, int x, int y)
{
	if (y == 0 || x == 0 || y == map->ver - 1 || x == map->hor - 1)
		return (1);
	if (!map->pl_available && ((texture == 9) || (texture == 0
							&& !map->pl_pos[0] && !map->pl_pos[1])))
	{
		map->pl_pos[0] = y;
		map->pl_pos[1] = x;
		if (texture == 9)
			map->pl_available = 1;
	}
	return (1);
}

void	set_sectors(int y, int x, t_map *map, int fd)
{
	int		i;
	int		texture;
	char	*line;

	while (++y < map->ver && (x = -1))
	{
		i = 0;
		get_next_line(fd, &line);
		while (++x < map->hor)
		{
			texture = ft_atoi_ptr(&i, line);
			if (texture > 9 || texture < 0)
				print_error_and_close(3);
			if ((texture == 0 || texture == 9)
			&& set_player_pos(map, texture, x, y)
				&& (y == 0 || x == 0 || y == map->ver - 1 || x == map->hor - 1))
				map->sectors[y][x].texture = 1;
			else
				map->sectors[y][x].texture = (texture == 9) ? 0 : texture;
			i++;
		}
		ft_strdel(&line);
	}
	if (map->pl_pos[0] == 0 && map->pl_pos[1] == 0)
		exit(0);
}

int		check_line(char *line)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] && i < (int)len)
	{
		if ((line[i] == '-' || line[i] == ' '
		|| (line[i] >= '0' && line[i] <= '9')) && i < (int)len)
			i++;
		else
			return (-1);
	}
	return (1);
}

int		check_file(int *ver, int *hor, int fd)
{
	int		res;
	int		gnl;
	char	*line;

	while (1)
	{
		if ((gnl = get_next_line(fd, &line)) < 1)
			return (gnl);
		if (*hor == 0)
			if ((*hor = my_ft_wordscount(line, ' ')) == 0)
			{
				ft_strdel(&line);
				return (-1);
			}
		if (*hor != my_ft_wordscount(line, ' '))
		{
			ft_strdel(&line);
			return (-1);
		}
		res = check_line(line);
		ft_strdel(&line);
		(*ver)++;
		if (res <= 0)
			return (res);
	}
}

void	valid_and_parse(char **argv, t_mod *mod)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (check_file(&mod->map->ver, &mod->map->hor, fd) < 0)
		print_error_and_close(0);
	init_map(mod->map);
	if (mod->map->hor <= 2 || mod->map->ver <= 2
		|| mod->map->hor > 100 || mod->map->ver > 100)
		print_error_and_close(1);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	set_sectors(-1, -1, mod->map, fd);
}
