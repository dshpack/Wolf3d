/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ft_wordscount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 03:32:57 by dshpack           #+#    #+#             */
/*   Updated: 2018/03/14 03:33:01 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		my_ft_wordscount(char const *str, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!str || !c)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}
