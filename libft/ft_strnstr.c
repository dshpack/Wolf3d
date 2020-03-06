/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 04:25:06 by dshpack           #+#    #+#             */
/*   Updated: 2018/01/21 04:25:08 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len2;

	len2 = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (needle[len2])
		len2++;
	while (*haystack && len >= len2)
	{
		if (ft_strncmp(haystack, needle, len2) == 0)
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
