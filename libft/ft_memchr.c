/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 04:09:44 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/20 04:09:48 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*source;

	source = (unsigned char*)s;
	while (n)
	{
		if (*source == (unsigned char)c)
			return (source);
		source++;
		n--;
	}
	return (NULL);
}
