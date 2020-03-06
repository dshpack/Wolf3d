/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshpack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 20:29:38 by dshpack           #+#    #+#             */
/*   Updated: 2018/03/23 20:29:46 by dshpack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *fin;

	if (lst && f)
	{
		fin = f(lst);
		res = fin;
		while (lst->next)
		{
			res->next = f(lst->next);
			res = res->next;
			lst = lst->next;
		}
		return (fin);
	}
	return (NULL);
}
