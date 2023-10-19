/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:01:55 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 01:22:25 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_libstst **lst, void (*del)(void*))
{
	t_libstst	*temp;
	t_libstst	*copylst;

	if ((*lst) == NULL || del == NULL)
		return ;
	copylst = (*lst);
	while (copylst)
	{
		(*del)(copylst->content);
		temp = copylst->next;
		free(copylst);
		copylst = temp;
	}
	(*lst) = NULL;
}
/*
{
	if (!del || !lst)
		return ;
	del(lst->content);
	free (lst);
	lst = NULL;
}

{
	t_libstst	*temp;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		*temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}
*/
