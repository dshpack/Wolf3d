/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 03:27:24 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/21 03:27:27 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	leng;
	size_t	len;

	if (*needle == '\0')
		return ((char *)haystack);
	leng = ft_strlen(needle);
	len = ft_strlen(haystack);
	while (*haystack != '\0' && len >= leng)
	{
		if (ft_strncmp(haystack, needle, leng) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
