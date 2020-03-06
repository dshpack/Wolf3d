/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 00:58:09 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/21 00:58:12 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	resl;
	size_t	lendst;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	i = 0;
	if (size <= lendst)
		return (size + lensrc);
	resl = lensrc + lendst;
	while (src[i])
	{
		if (lendst < size - 1)
		{
			dst[lendst] = src[i];
			lendst++;
		}
		i++;
	}
	dst[lendst] = '\0';
	return (resl);
}
