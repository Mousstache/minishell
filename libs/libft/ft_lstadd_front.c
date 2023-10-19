/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:41:04 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/19 21:14:12 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_libstst **lst, t_libstst *new)
{
	if (!lst)
		new->next = NULL;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int	main(void)
{
	t_libstst	*list1;
	t_libstst	*list2;

	list1 = ft_lstnew("jean luc lemoine");
	list2 = ft_lstnew("grosse tete");
	ft_lstadd_front(list1, list2);
}
*/
