/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:11:57 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/19 18:12:01 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		(*(unsigned char *)dst) = (*(unsigned char *)src);
		if ((*(unsigned char *)src) == (unsigned char)c)
			return (dst + 1);
		src++;
		dst++;
		n--;
	}
	return (NULL);
}
