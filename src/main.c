/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:53:12 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/17 20:53:15 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		draw_pix(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *target_pixel;

	target_pixel = (Uint32 *)(
			(Uint8 *)surface->pixels + y * surface->pitch + x * sizeof(Uint32));
	*target_pixel = pixel;
}

int			ft_atoi_ptr(int *i, char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
			&& (str[*i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
			&& (str[*i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[*i] - 48);
		(*i)++;
	}
	return ((int)res * sign);
}

void		draw_minimap(t_mod *mod, t_graphic *graph)
{
	t_draw_map		d_map;

	d_map.i = 0;
	d_map.y = 9;
	d_map.blue = 0x4286f4;
	d_map.red = 0xf44162;
	d_map.x_y_max = (mod->map->hor < 12 && mod->map->ver < 12) ? 210 : 410;
	d_map.sector_x = (mod->map->hor > mod->map->ver) ?
		d_map.x_y_max / mod->map->hor : d_map.x_y_max / mod->map->ver;
	d_map.sector_y = d_map.sector_x;
	while (++d_map.i <= mod->map->ver)
	{
		while (++d_map.y < d_map.sector_y * d_map.i + 9)
		{
			d_map.j = 0;
			d_map.x = 9;
			while (++d_map.j <= mod->map->hor)
				while (++d_map.x < d_map.sector_x * d_map.j + 9)
					if (mod->map->sectors[d_map.i - 1][d_map.j - 1].texture > 0)
						draw_pix(graph->screen, d_map.x, d_map.y, d_map.blue);
					else
						draw_pix(graph->screen, d_map.x, d_map.y, d_map.red);
		}
	}
}

void		event_handler(t_mod *mod, t_sts *sts)
{
	SDL_Event	evnt;

	sts->is_rotating = 0;
	while (SDL_PollEvent(&evnt) != 0)
	{
		if (evnt.type == SDL_QUIT
		|| evnt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			sts->exit = 1;
		kb_up_handler(mod, evnt, evnt.key.keysym.sym);
		kb_dw_handler(mod, evnt, evnt.key.keysym.sym);
		if (evnt.type == SDL_MOUSEMOTION)
		{
			(evnt.motion.xrel < 0) ? (sts->is_rotating = -1) : 0;
			(evnt.motion.xrel > 0) ? (sts->is_rotating = 1) : 0;
		}
		if (evnt.type == SDL_MOUSEWHEEL)
		{
			if (evnt.wheel.y > 0 && mod->ray.zoom < 15)
				mod->ray.zoom += 0.25;
			else if (evnt.wheel.y < 0 && mod->ray.zoom > 1)
				mod->ray.zoom -= 0.25;
		}
	}
	moveing(mod, &mod->ray);
	rotating(mod, &mod->ray, mod->ray.rot_speed);
}

int			main(int argc, char **argv)
{
	t_mod		mod;

	if (argc > 1)
	{
		global_initialisation(&mod);
		valid_and_parse(argv, &mod);
		if (init_graphics(&mod))
		{
			while (!mod.sts->exit)
			{
				if (mod.is_game)
					enter_point(&mod, &mod.menu);
				else
					game_point(&mod, mod.graph);
				SDL_UpdateWindowSurface(mod.graph->window);
			}
			close_window(mod.graph);
		}
	}
	else
		print_error_and_close(1);
	return (0);
}
