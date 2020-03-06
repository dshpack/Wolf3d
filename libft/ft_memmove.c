/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:53:04 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/19 21:53:07 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*destination;
	unsigned char	*sourche;
	size_t			i;

	destination = (unsigned char *)dst;
	sourche = (unsigned char *)src;
	if (destination > sourche)
	{
		while (len--)
		{
			destination[len] = sourche[len];
		}
		return (destination);
	}
	i = 0;
	while (i < len)
	{
		destination[i] = sourche[i];
		i++;
	}
	return (destination);
}
