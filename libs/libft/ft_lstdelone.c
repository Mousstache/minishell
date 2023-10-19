/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:41:55 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/19 21:14:12 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_libstst *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	del(lst->content);
	free (lst);
	lst = NULL;
}
