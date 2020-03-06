/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 06:51:31 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/20 06:51:42 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*src;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	src = (char *)malloc(sizeof(char) * (i + 1));
	if (src == NULL)
		return (NULL);
	len = i;
	i = 0;
	while (s1[i])
	{
		src[i] = s1[i];
		i++;
	}
	src[len] = '\0';
	return (src);
}
