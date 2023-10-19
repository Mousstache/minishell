/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:29:17 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/21 03:41:55 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	char str[8] = "avion";
	printf("%p", ft_memchr(str, 'i', 5));
	printf("\n%p", memchr(str, 'i', 5));
	return 0;
}
//pq cas d erreur si pas caster  char c ??
*/
