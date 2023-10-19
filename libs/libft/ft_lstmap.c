/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:34:09 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/19 21:14:12 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libstst	*ft_lstmap(t_libstst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_libstst	*new;
	t_libstst	*copynew;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!lst)
		return (NULL);
	copynew = new;
	lst = lst->next;
	while (lst != NULL)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&copynew, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (copynew);
}
