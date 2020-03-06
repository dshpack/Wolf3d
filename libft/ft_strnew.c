/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:46:48 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/22 18:46:53 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char*)malloc(sizeof(char) * (size + 1));
	if (p == NULL)
		return (NULL);
	while (i < size)
	{
		p[i] = '\0';
		i++;
	}
	p[i] = '\0';
	return (p);
}
