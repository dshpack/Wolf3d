/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 03:37:24 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/29 03:37:29 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		cast_on_floor(t_mod *mod, t_ray *ray, int x)
{
	int		y;

	y = ray->d_end;
	while (y < WIN_HEIGHT)
	{
		ray->cur_dist = mod->graph->height / (2.0 * y - mod->graph->height);
		ray->weight = (ray->cur_dist - ray->pl_dist)
			/ (ray->dist_wall - ray->pl_dist);
		ray->cur_flor_x =
			ray->weight * ray->x_wall_floor + (1.0 - ray->weight) * ray->x_pos;
		ray->cur_flor_y =
			ray->weight * ray->y_wall_floor + (1.0 - ray->weight) * ray->y_pos;
		ray->tex_x_floor = (int)(ray->cur_flor_x * TEX_WIDTH) % TEX_WIDTH;
		ray->tex_y_floor = (int)(ray->cur_flor_y * TEX_HEIGHT) % TEX_HEIGHT;
		mod->img = mod->tex_img[ray->tex_num]->pixels;
		mod->buf[mod->graph->width * y + x] =
			mod->img[TEX_WIDTH * ray->tex_y_floor + ray->tex_x_floor] >> 1;
		mod->buf[mod->graph->width * (mod->graph->height - y) + x] =
			mod->img[TEX_WIDTH * ray->tex_y_floor + ray->tex_x_floor];
		y++;
	}
}

void		prepare(t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = ray->x_dir * ray->zoom + ray->x_plane * ray->cam_x;
	ray->dir_y = ray->y_dir * ray->zoom + ray->y_plane * ray->cam_x;
	ray->x_map = (int)ray->x_pos;
	ray->y_map = (int)ray->y_pos;
	ray->dist_x_delta = fabs(1 / ray->dir_x);
	ray->dist_y_delta = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->step_x = (ray->dir_x < 0) ? -1 : 1;
	if (ray->dir_x < 0)
		ray->dist_side_x = (ray->x_pos - ray->x_map) * ray->dist_x_delta;
	else
		ray->dist_side_x = (ray->x_map + 1.0 - ray->x_pos) * ray->dist_x_delta;
	ray->step_y = (ray->dir_y < 0) ? -1 : 1;
	if (ray->dir_y < 0)
		ray->dist_side_y = (ray->y_pos - ray->y_map) * ray->dist_y_delta;
	else
		ray->dist_side_y = (ray->y_map + 1.0 - ray->y_pos) * ray->dist_y_delta;
}

void		chose_side(t_mod *mod, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->dist_side_x < ray->dist_side_y)
		{
			ray->dist_side_x += ray->dist_x_delta;
			ray->x_map += ray->step_x;
			ray->s = 0;
		}
		else
		{
			ray->dist_side_y += ray->dist_y_delta;
			ray->y_map += ray->step_y;
			ray->s = 1;
		}
		if (mod->map->sectors[ray->x_map][ray->y_map].texture > 0)
			ray->hit = 1;
	}
	ray->wall_dist = (ray->s == 0) ?
		(ray->x_map - ray->x_pos + (1 - ray->step_x) / 2) / ray->dir_x :
		(ray->y_map - ray->y_pos + (1 - ray->step_y) / 2) / ray->dir_y;
}

void		wall_draw(t_mod *mod, t_ray *ray, int x, int tex_num)
{
	Uint32	color;
	int		y;

	y = ray->d_end;
	ray->d_end = ray->height_line / 2 + WIN_HEIGHT / 2;
	if (ray->d_end >= WIN_HEIGHT)
		ray->d_end = WIN_HEIGHT - 1;
	ray->wall_x = (ray->s == 0) ? ray->y_pos + ray->wall_dist * ray->dir_y :
									ray->x_pos + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)(TEX_WIDTH));
	if ((ray->s == 0 && ray->dir_x > 0) || (ray->s == 1 && ray->dir_y < 0))
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	y = ray->d_start;
	while (++y < ray->d_end)
	{
		ray->d = y * 256 - WIN_HEIGHT * 128 + ray->height_line * 128;
		ray->tex_y = ((ray->d * TEX_HEIGHT) / ray->height_line) / 256;
		mod->img = mod->tex_img[tex_num]->pixels;
		color = mod->img[TEX_HEIGHT * ray->tex_y + ray->tex_x];
		if (ray->s == 1)
			color = (color >> 1) & 8355711;
		mod->buf[mod->graph->width * y + x] = color;
	}
}

void		ray_cast(t_mod *mod, t_ray *ray)
{
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		prepare(ray, x);
		chose_side(mod, ray);
		ray->height_line = (int)(WIN_HEIGHT / ray->wall_dist);
		ray->d_start = -ray->height_line / 2 + WIN_HEIGHT / 2;
		if (ray->d_start < 0)
			ray->d_start = 0;
		if (ray->s == 0 && ray->dir_x > 0)
			wall_draw(mod, ray, x, 0);
		else if (ray->s == 0 && ray->dir_x < 0)
			wall_draw(mod, ray, x, 1);
		else if (ray->s == 1 && ray->dir_y > 0)
			wall_draw(mod, ray, x, 2);
		else if (ray->s == 1 && ray->dir_y < 0)
			wall_draw(mod, ray, x, 3);
		cast_on_floor(mod, ray, x);
		x++;
	}
}
