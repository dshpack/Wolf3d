/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:20:27 by dshpack           #+#    #+#             */
/*   Updated: 2018/03/24 16:48:42 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*current;

	current = *alst;
	if (!*alst || !del)
		return ;
	while (current)
	{
		current = current->next;
		ft_lstdelone(alst, del);
		*alst = current;
	}
	*alst = NULL;
}
