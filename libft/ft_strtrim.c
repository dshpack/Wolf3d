/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:41:28 by dshpack           #+#    #+#             */
/*   Updated: 2018/02/10 16:41:31 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	int		i;
	int		i2;
	char	*p;

	i = 0;
	i2 = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (len > i && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'
		|| s[len] == '\0'))
		len--;
	p = (char*)malloc(sizeof(char) * (len - i + 2));
	if (!p)
		return (NULL);
	while (i <= len)
		p[i2++] = s[i++];
	p[i2] = '\0';
	return (p);
}
