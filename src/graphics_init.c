/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:05:00 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/24 18:05:00 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		global_initialisation(t_mod *mod)
{
	ft_bzero(mod, sizeof(t_mod));
	if (!(mod->map = (t_map *)malloc(sizeof(t_map))))
		print_error_and_close(2);
	ft_bzero(mod->map, sizeof(t_map));
	if (!(mod->graph = (t_graphic *)malloc(sizeof(t_graphic))))
		print_error_and_close(2);
	ft_bzero(mod->graph, sizeof(t_graphic));
	if (!(mod->sts = (t_sts *)malloc(sizeof(t_sts))))
		print_error_and_close(2);
	ft_bzero(mod->sts, sizeof(t_sts));
	mod->sts->exit = 0;
}

int			init_window(t_graphic *graph)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else
	{
		graph->window = SDL_CreateWindow("Wolf3d by dshpack",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				graph->width, graph->height, SDL_WINDOW_SHOWN);
		if (!graph->window)
			SDL_Log("Window could not be created!"
					"SDL_Error: %s\n", SDL_GetError());
		else
		{
			graph->screen = SDL_GetWindowSurface(graph->window);
			return (1);
		}
	}
	return (1);
}

void		init_map(t_map *map)
{
	int		i;
	int		j;
	int		hor;
	int		ver;

	i = -1;
	hor = map->hor;
	ver = map->ver;
	if (!(map->sectors = (t_sector **)malloc(sizeof(t_sector *) * ver)))
		print_error_and_close(2);
	while (++i < ver)
	{
		if (!(map->sectors[i] = (t_sector *)malloc(sizeof(t_sector) * hor)))
			exit(0);
		j = -1;
		while (++j < hor)
			map->sectors[i][j].texture = 0;
	}
	map->pl_pos[0] = 0;
	map->pl_pos[1] = 0;
	map->pl_available = 0;
}

t_graphic	*init_structs_and_working_data(t_mod *m)
{
	t_graphic		*graph;

	graph = m->graph;
	m->is_game = 1;
	if (TTF_Init() == -1)
	{
		ft_putstr("Can't initialize ttf");
		exit(0);
	}
	upload_ttf(m);
	upload_menu_img(m);
	init_ttf(&m->menu);
	graph->width = WIN_WIDTH;
	graph->height = WIN_HEIGHT;
	graph->window = NULL;
	graph->screen = NULL;
	return (graph);
}

int			init_graphics(t_mod *m)
{
	t_graphic		*graph;

	graph = init_structs_and_working_data(m);
	m->ray.x_pos = m->map->pl_pos[0] + 0.5;
	m->ray.y_pos = m->map->pl_pos[1] + 0.5;
	m->ray.x_dir = -1.0;
	m->ray.y_dir = 0.0;
	m->ray.x_plane = 0.0;
	m->ray.y_plane = 0.66;
	m->ray.zoom = 1;
	m->ray.move_speed = 0.24;
	m->ray.rot_speed = 4.2 * M_PI / 180;
	m->sur =
		SDL_CreateRGBSurface(0, graph->width, graph->height, 32, 0, 0, 0, 0);
	m->buf = (Uint32 *)m->sur->pixels;
	if (!init_window(m->graph))
	{
		SDL_Log("Failed to load media!\n");
		return (0);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}
