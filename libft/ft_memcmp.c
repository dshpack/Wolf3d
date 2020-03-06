/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 04:38:22 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/20 04:38:27 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if ((*(unsigned char*)s1) != (*(unsigned char*)s2))
		{
			return ((*(unsigned char*)s1) - (*(unsigned char*)s2));
		}
		s1++;
		s2++;
	}
	return (0);
}
