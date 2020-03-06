/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 22:27:00 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/17 22:27:00 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		init_ttf(t_menu *menu)
{
	t_txt	txt[3];

	menu->picked = 1;
	txt[0].txt = "Start";
	txt[1].txt = "Exit";
	txt[2].txt = "UP/DOWN - arrows to select, E - make choice";
	txt[0].col = (SDL_Color){255, 255, 255, 0};
	txt[1].col = (SDL_Color){255, 0, 0, 0};
	txt[2].col = (SDL_Color){255, 255, 255, 0};
	menu->picked = 0;
	menu->opt[0] = TTF_RenderText_Solid(menu->font[0], txt[0].txt, txt[0].col);
	menu->opt[1] = TTF_RenderText_Solid(menu->font[0], txt[0].txt, txt[1].col);
	menu->opt[2] = TTF_RenderText_Solid(menu->font[0], txt[1].txt, txt[0].col);
	menu->opt[3] = TTF_RenderText_Solid(menu->font[0], txt[1].txt, txt[1].col);
	menu->opt[4] = TTF_RenderText_Solid(menu->font[1], txt[2].txt, txt[2].col);
	menu->pos[0].x = menu->img->clip_rect.w - 200 - menu->opt[0]->clip_rect.w;
	menu->pos[0].y = menu->img->clip_rect.h - 200 - menu->opt[0]->clip_rect.h;
	menu->pos[1].x = menu->img->clip_rect.w - 200 - menu->opt[1]->clip_rect.w;
	menu->pos[1].y = menu->img->clip_rect.h - 100 - menu->opt[1]->clip_rect.h;
	menu->pos[2].x = menu->img->clip_rect.w - 1700 - menu->opt[2]->clip_rect.w;
	menu->pos[2].y = menu->img->clip_rect.h - 10 - menu->opt[2]->clip_rect.h;
}

void		upload_ttf(t_mod *main)
{
	main->menu.font[0] = TTF_OpenFont("./resources/font/wolf.ttf", 80);
	main->menu.font[1] = TTF_OpenFont("./resources/font/arial.ttf", 20);
	if (main->menu.font[0] == NULL || main->menu.font[1] == NULL)
	{
		ft_putstr("Can't upload font");
		exit(0);
	}
}

void		upload_menu_img(t_mod *mod)
{
	mod->menu.img = ft_get_img("resources/menu_img/1.png");
	mod->tex_img = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 8);
	mod->tex_img[0] = ft_get_img("resources/textures/eagle.png");
	mod->tex_img[1] = ft_get_img("resources/textures/red_brick.png");
	mod->tex_img[2] = ft_get_img("resources/textures/purple_stone.png");
	mod->tex_img[3] = ft_get_img("resources/textures/grey_stone.png");
	mod->tex_img[4] = ft_get_img("resources/textures/blue_stone.png");
	mod->tex_img[5] = ft_get_img("resources/textures/mossy.png");
	mod->tex_img[6] = ft_get_img("resources/textures/wood.png");
	mod->tex_img[7] = ft_get_img("resources/textures/color_stone.png");
}

SDL_Surface	*ft_get_img(char *path)
{
	SDL_Surface		*optimized;
	SDL_Surface		*tmp;
	SDL_PixelFormat	sdl_format;

	sdl_format.format = SDL_PIXELFORMAT_ARGB8888;
	sdl_format.BytesPerPixel = 4;
	sdl_format.BitsPerPixel = 32;
	sdl_format.palette = NULL;
	sdl_format.Rmask = 0;
	sdl_format.Gmask = 0;
	sdl_format.Bmask = 0;
	sdl_format.Amask = 0;
	optimized = NULL;
	if ((tmp = IMG_Load(path)) != NULL)
	{
		optimized = SDL_ConvertSurface(tmp, &sdl_format, 0);
		SDL_FreeSurface(tmp);
	}
	if (optimized == NULL)
	{
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
	}
	return (optimized);
}
