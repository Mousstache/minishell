/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:40:00 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/16 15:41:33 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	int				len;
	unsigned int	nb;
	char			*str;

	nb = n;
	i = (n < 0);
	len = ft_count(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	str[len] = 0;
	while (--len >= i)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	 printf("%s\n", ft_itoa(5645));
	 printf("%s\n", ft_itoa(-1234));
	printf("%s\n", ft_itoa(1));
	//printf("count=%i\n", ft_count(-1));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
}

#include "libft.h"

*/
