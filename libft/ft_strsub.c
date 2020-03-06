/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:43:40 by dshpack           #+#    #+#             */
/*   Updated: 2018/02/10 14:43:57 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	c = (char*)malloc(sizeof(char) * (len + 1));
	if (!c)
		return (NULL);
	while (*s && (int)len > 0)
	{
		c[i] = s[start];
		i++;
		start++;
		len--;
	}
	c[i] = '\0';
	return (c);
}
