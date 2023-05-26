/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:15:44 by motroian          #+#    #+#             */
/*   Updated: 2023/01/25 14:44:21 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_liste *lst, void (*f)(void *))
{
	while (lst && lst != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
