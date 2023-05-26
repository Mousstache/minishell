/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:15:55 by motroian          #+#    #+#             */
/*   Updated: 2023/01/25 14:44:06 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_liste	*ft_lstmap(t_liste *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*liste;
	t_list	*tmp;

	if (!f || !del)
		return (NULL);
	list = NULL;
	while (lst && lst != NULL)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			while (list)
			{
				tmp = list->next;
				(*del)(list->content);
				free(list);
				list = tmp;
			}
			lst = NULL;
		}
		ft_lstadd_back(&list, tmp);
		lst = lst->next;
	}
	return (list);
}
