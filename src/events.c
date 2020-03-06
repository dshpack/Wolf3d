/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:23:00 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/26 18:23:00 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		kb_up_handler(t_mod *mod, SDL_Event evnt, SDL_Keycode key)
{
	if (evnt.type == SDL_KEYUP)
	{
		if (key == SDLK_UP || key == SDLK_w
		|| key == SDLK_DOWN || key == SDLK_s)
			mod->sts->is_move = 0;
		else if (key == SDLK_LEFT || key == SDLK_q
			|| key == SDLK_RIGHT || key == SDLK_e)
			mod->sts->is_rotating = 0;
		else if (key == SDLK_a)
			mod->sts->is_straf = 0;
		else if (key == SDLK_d)
			mod->sts->is_straf = 0;
		else if (key == SDLK_SPACE)
			mod->sts->is_menu = 0;
		else if (key == SDLK_m)
			mod->sts->is_map = 0;
	}
}

void		kb_dw_handler(t_mod *mod, SDL_Event evnt, SDL_Keycode key)
{
	if (evnt.type == SDL_KEYDOWN)
	{
		if (key == SDLK_UP || key == SDLK_w)
			mod->sts->is_move = 1;
		else if (key == SDLK_DOWN || key == SDLK_s)
			mod->sts->is_move = -1;
		else if (key == SDLK_LEFT || key == SDLK_q)
			mod->sts->is_rotating = -1;
		else if (key == SDLK_RIGHT || key == SDLK_e)
			mod->sts->is_rotating = 1;
		else if (key == SDLK_a)
			mod->sts->is_straf = -1;
		else if (key == SDLK_d)
			mod->sts->is_straf = 1;
		else if (key == SDLK_SPACE)
		{
			mod->sts->is_menu = 1;
			mod->sts->is_map = 0;
		}
		else if (key == SDLK_m)
		{
			mod->sts->is_map = 1;
			mod->sts->is_menu = 0;
		}
	}
}

void		moveing(t_mod *mod, t_ray *ray)
{
	if (mod->sts->is_move == 1)
	{
		if (mod->map->sectors
			[(int)(ray->x_pos + ray->x_dir * ray->move_speed * 4.2)]
			[(int)(ray->y_pos)].texture == 0)
			ray->x_pos += ray->x_dir * ray->move_speed;
		if (mod->map->sectors
			[(int)(ray->x_pos)]
			[(int)(ray->y_pos + ray->y_dir
			* ray->move_speed * 4.2)].texture == 0)
			ray->y_pos += ray->y_dir * ray->move_speed;
	}
	if (mod->sts->is_move == -1)
	{
		if (mod->map->sectors
			[(int)(ray->x_pos - ray->x_dir * ray->move_speed * 4.2)]
			[(int)(ray->y_pos)].texture == 0)
			ray->x_pos -= ray->x_dir * ray->move_speed;
		if (mod->map->sectors
			[(int)(ray->x_pos)]
			[(int)(ray->y_pos - ray->y_dir
			* ray->move_speed * 4.2)].texture == 0)
			ray->y_pos -= ray->y_dir * ray->move_speed;
	}
	strafing(mod, &mod->ray);
}

void		strafing(t_mod *mod, t_ray *ray)
{
	if (mod->sts->is_straf == 1)
	{
		if (mod->map->sectors
			[(int)(ray->x_pos + mod->ray.x_plane * ray->move_speed * 4.2)]
			[(int)(ray->y_pos)].texture == 0)
			ray->x_pos += mod->ray.x_plane * ray->move_speed;
		if (mod->map->sectors
			[(int)(ray->x_pos)]
			[(int)(ray->y_pos + mod->ray.y_plane
								* ray->move_speed * 4.2)].texture == 0)
			ray->y_pos += mod->ray.y_plane * ray->move_speed;
	}
	if (mod->sts->is_straf == -1)
	{
		if (mod->map->sectors
			[(int)(ray->x_pos - mod->ray.x_plane * ray->move_speed * 4.2)]
			[(int)(ray->y_pos)].texture == 0)
			ray->x_pos -= mod->ray.x_plane * ray->move_speed;
		if (mod->map->sectors
			[(int)(ray->x_pos)]
			[(int)(ray->y_pos - mod->ray.y_plane
								* ray->move_speed * 4.2)].texture == 0)
			ray->y_pos -= mod->ray.y_plane * ray->move_speed;
	}
}

void		rotating(t_mod *mod, t_ray *ray, double rot_speed)
{
	if (mod->sts->is_rotating == 1)
	{
		ray->dir_x_old = ray->x_dir;
		ray->x_dir = ray->x_dir * cos(-rot_speed) - ray->y_dir
				* sin(-rot_speed);
		ray->y_dir = ray->dir_x_old * sin(-rot_speed)
				+ ray->y_dir * cos(-rot_speed);
		ray->old_plane_x = ray->x_plane;
		ray->x_plane =
			ray->x_plane * cos(-rot_speed) - ray->y_plane * sin(-rot_speed);
		ray->y_plane =
			ray->old_plane_x * sin(-rot_speed) + ray->y_plane * cos(-rot_speed);
	}
	if (mod->sts->is_rotating == -1)
	{
		ray->dir_x_old = ray->x_dir;
		ray->x_dir = ray->x_dir * cos(rot_speed) - ray->y_dir * sin(rot_speed);
		ray->y_dir = ray->dir_x_old * sin(rot_speed) + ray->y_dir
				* cos(rot_speed);
		ray->old_plane_x = ray->x_plane;
		ray->x_plane =
			ray->x_plane * cos(rot_speed) - ray->y_plane * sin(rot_speed);
		ray->y_plane =
			ray->old_plane_x * sin(rot_speed) + ray->y_plane * cos(rot_speed);
	}
}
