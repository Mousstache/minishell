/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:54:10 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/20 19:40:14 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define PTITNOM 18446744073709551615UL

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size == PTITNOM || nmemb == PTITNOM)
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_bzero (tab, nmemb * size);
	return (tab);
}
