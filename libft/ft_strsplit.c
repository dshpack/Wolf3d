/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:02:43 by dshpack           #+#    #+#             */
/*   Updated: 2018/02/10 18:02:47 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		word;
	char	**str;
	int		j;
	int		i;
	int		letter;

	word = my_ft_wordscount(s, c);
	i = 0;
	if (!(str = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	str[word] = NULL;
	while (i < word)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		letter = my_ft_leterlength(s, c);
		if (!(str[i] = (char *)malloc(sizeof(char) * (letter + 1))))
			return (NULL);
		while (letter--)
			str[i][j++] = *s++;
		str[i++][j] = '\0';
	}
	return (str);
}
