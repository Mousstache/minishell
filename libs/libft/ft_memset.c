/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:42 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/15 22:26:02 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	s = str;
	return (s);
}
/*
int main(void)
{
	char str[5]= "testi";
	printf("\n%s", str);
	printf("\n%p",ft_memset(str, 5, 2));
	printf("\n%s", str);
	printf("\n%p",memset(str, 5, 2));
	printf("\n%s", str);
	return 0;
}
*/
