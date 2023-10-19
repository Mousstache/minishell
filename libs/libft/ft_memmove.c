/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:09 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/20 20:31:31 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*mdest;
	char	*msrc;

	mdest = (char *)dest;
	msrc = (char *)src;
	if (dest == src)
		return (dest);
	if (dest < src)
		ft_memcpy(mdest, msrc, n);
	else
	{
		while (n-- > 0)
			mdest[n] = msrc[n];
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	//char	*dest;
	//dest = src + 1;

	printf("%s", ft_memmove(src+ 8, src, 10));
	return(0);
}
*/
