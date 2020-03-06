/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ft_resize_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 19:35:19 by dshpack           #+#    #+#             */
/*   Updated: 2018/03/24 19:35:22 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_ft_resize_s(char *s, int n)
{
	int		massyze;
	char	*newmas;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	massyze = (int)ft_strlen(s);
	newmas = ft_strnew(n + massyze);
	while (*s)
	{
		newmas[i] = *s;
		i++;
		s++;
	}
	ft_strdel(&s);
	return (newmas);
}
