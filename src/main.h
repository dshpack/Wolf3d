/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:53:40 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/17 20:53:45 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# include <fcntl.h>
# include "../libft/libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_timer.h"
# include "SDL_ttf.h"

typedef struct		s_draw_map
{
	int				i;
	int				j;
	int				x;
	int				y;
	int				sector_x;
	int				sector_y;
	int				blue;
	Uint32			red;
	Uint32			x_y_max;
}					t_draw_map;

typedef struct		s_sector
{
	int				texture;
}					t_sector;

typedef struct		s_graphics
{
	int				width;
	int				height;
	SDL_Window		*window;
	SDL_Surface		*screen;
}					t_graphic;

typedef struct		s_map
{
	int				ver;
	int				hor;
	int				pl_available;
	int				pl_pos[2];
	t_sector		**sectors;
}					t_map;

typedef struct		s_status
{
	char			exit;
	char			is_move;
	char			is_straf;
	char			is_rotating;
	char			is_menu;
	char			is_map;
}					t_sts;

typedef struct		s_menu
{
	int				picked;
	TTF_Font		*font[2];
	SDL_Rect		pos[9];
	SDL_Color		color[3];
	const char		*txt[6];
	SDL_Surface		*img;
	SDL_Surface		*opt[13];
}					t_menu;

typedef struct		s_text
{
	SDL_Rect		pos;
	SDL_Color		col;
	const char		*txt;
}					t_txt;

typedef struct		s_raycasting
{
	int				x_map;
	int				y_map;
	double			cam_x;
	double			dir_x;
	double			dir_y;
	double			x_pos;
	double			y_pos;
	double			x_dir;
	double			y_dir;
	double			x_plane;
	double			y_plane;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				s;
	int				hit;
	double			dist_side_x;
	double			dist_side_y;
	double			dist_x_delta;
	double			dist_y_delta;
	int				height_line;
	int				d_start;
	int				d_end;
	double			cur_dist;
	double			dir_x_old;
	double			old_plane_x;
	int				tex_num;
	double			wall_x;
	int				d;
	int				tex_y;
	int				tex_x;
	double			weight;
	double			cur_flor_x;
	double			cur_flor_y;
	double			x_wall_floor;
	double			y_wall_floor;
	int				tex_x_floor;
	int				tex_y_floor;
	int				pl_dist;
	double			dist_wall;
	double			move_speed;
	double			rot_speed;
	double			zoom;
}					t_ray;

typedef struct		s_main_module
{
	t_map			*map;
	t_graphic		*graph;
	t_sts			*sts;
	t_ray			ray;
	t_menu			menu;
	int				is_game;
	Uint32			*img;
	SDL_Surface		*sur;
	Uint32			*buf;
	SDL_Event		menu_keys;
	SDL_Surface		**tex_img;
}					t_mod;

int					check_file(int *ver, int *hor, int fd);
int					init_graphics(t_mod *m);
void				init_map(t_map *map);
void				global_initialisation(t_mod *mod);
void				set_sectors(int y, int x, t_map *map, int fd);
void				event_handler(t_mod *mod, t_sts *sts);
void				valid_and_parse(char **argv, t_mod *mod);
SDL_Surface			*ft_get_img(char *path);
void				ray_cast(t_mod *mod, t_ray *ray);
void				game_point(t_mod *mod, t_graphic *graph);
void				enter_point(t_mod *mod, t_menu *m);
void				print_error_and_close(int flag);
int					init_window(t_graphic *graph);
int					ft_atoi_ptr(int *i, char *str);
void				draw_minimap(t_mod *mod, t_graphic *graph);
void				draw_pix(SDL_Surface *surface, int x, int y, Uint32 pixel);
void				close_window(t_graphic *graph);
void				init_ttf(t_menu *menu);
void				upload_ttf(t_mod *main);
void				upload_menu_img(t_mod *mod);
void				moveing(t_mod *mod, t_ray *ray);
void				strafing(t_mod *mod, t_ray *ray);
void				rotating(t_mod *mod, t_ray *ray, double rot_speed);
void				kb_dw_handler(t_mod *mod, SDL_Event evnt, SDL_Keycode key);
void				kb_up_handler(t_mod *mod, SDL_Event evnt, SDL_Keycode key);

#endif
