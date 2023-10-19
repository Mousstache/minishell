/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:47:40 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/20 21:58:05 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libstst	*ft_lstlast(t_libstst *lst)
{
	int			i;
	int			size;
	t_libstst	*temp;

	i = 0;
	if (!lst)
		return (lst);
	else
	{
		temp = lst;
		size = ft_lstsize(lst);
		while (i < size - 1)
		{
			temp = temp->next;
			i++;
		}
		return (temp);
	}
}
