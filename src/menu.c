/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 02:47:00 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/29 02:47:00 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_key_catcher(t_mod *main)
{
	if (SDL_WaitEvent(&main->menu_keys))
	{
		(main->menu_keys.type == SDL_QUIT ||
		main->menu_keys.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		? main->sts->exit = 1 : 0;
		if (main->menu_keys.type == SDL_KEYUP)
		{
			if (main->menu_keys.key.keysym.scancode == SDL_SCANCODE_UP ||
				main->menu_keys.key.keysym.scancode == SDL_SCANCODE_DOWN)
				main->menu.picked = (main->menu.picked == 0) ? 1 : 0;
			if (main->menu_keys.key.keysym.scancode == SDL_SCANCODE_E)
			{
				if (main->menu.picked == 0)
					main->is_game = 0;
				if (main->menu.picked == 1)
					main->sts->exit = 1;
			}
		}
	}
}

void		ft_key_catcher_2(t_mod *mod)
{
	if (SDL_WaitEvent(&mod->menu_keys))
	{
		SDL_UpdateWindowSurface(mod->graph->window);
		(mod->menu_keys.type == SDL_QUIT
		|| mod->menu_keys.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		? mod->sts->exit = 1 : 0;
		if (mod->menu_keys.type == SDL_KEYUP &&
			mod->menu_keys.key.keysym.scancode == SDL_SCANCODE_M)
			mod->sts->is_map = (mod->sts->is_map == 0) ? 1 : 0;
		if (mod->menu_keys.type == SDL_KEYUP &&
			mod->menu_keys.key.keysym.scancode == SDL_SCANCODE_SPACE)
			mod->sts->is_menu = (mod->sts->is_menu == 0) ? 1 : 0;
	}
}

void		enter_point(t_mod *mod, t_menu *m)
{
	if (mod->is_game == 1)
	{
		ft_key_catcher(mod);
		SDL_BlitSurface(m->img, NULL, mod->graph->screen, NULL);
		SDL_BlitSurface(m->opt[(m->picked) ? 0 : 1], NULL,
						mod->graph->screen, &m->pos[0]);
		SDL_BlitSurface(m->opt[(m->picked) ? 3 : 2], NULL,
						mod->graph->screen, &m->pos[1]);
		SDL_BlitSurface(m->opt[4], NULL, mod->graph->screen, &m->pos[2]);
	}
	else
	{
		ft_key_catcher_2(mod);
		SDL_BlitSurface(m->img, NULL, mod->graph->screen, NULL);
		SDL_BlitSurface(m->opt[(mod->sts->is_map) ? 6 : 5], NULL,
						mod->graph->screen, &m->pos[3]);
		SDL_BlitSurface(m->opt[(mod->sts->is_menu) ? 7 : 8], NULL,
						mod->graph->screen, &m->pos[4]);
	}
}

void		game_point(t_mod *mod, t_graphic *graph)
{
	event_handler(mod, mod->sts);
	ray_cast(mod, &mod->ray);
	SDL_BlitSurface(mod->sur, NULL, mod->graph->screen, NULL);
	if (mod->sts->is_map != 0)
		draw_minimap(mod, graph);
}
