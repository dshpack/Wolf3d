/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 21:02:07 by dshpack           #+#    #+#             */
/*   Updated: 2018/11/17 21:02:10 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		print_error_and_close_second(int flag)
{
	if (flag == 3)
		ft_putstr("\n"
				"===================================================\n"
				"= Sorry, input texture numbers wrong!             =\n"
				"= Only numbers between 0-9 including are allowed. =\n"
				"===================================================\n");
	else if (flag == 4)
		ft_putstr("\n"
				"=======================================================\n"
				"= There is no place for the player!                   =\n"
				"= There must be at least one zero or nine on the map. =\n"
				"=======================================================\n");
	exit(0);
}

void		print_error_and_close(int flag)
{
	if (flag == 0)
		ft_putstr("\n"
			"=======================================================\n"
			"= File with map is not entered or it is not readable! =\n"
			"=======================================================\n\n");
	else if (flag == 1)
		ft_putstr("\n"
			"=====================================================\n"
			"= Invalid map size!                                 =\n"
			"= Map size should be between 3x3 100x100 including. =\n"
			"=====================================================\n\n");
	else if (flag == 2)
		ft_putstr("\n"
			"======================================================\n"
			"=                 Sorry, memory low!                 =\n"
			"======================================================\n");
	else if (flag == 3 || flag == 4)
		print_error_and_close_second(flag);
	exit(0);
}

void		close_window(t_graphic *graph)
{
	SDL_DestroyWindow(graph->window);
	graph->window = NULL;
	SDL_Quit();
}
