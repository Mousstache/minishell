/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_src.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:31:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/30 20:12:28 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexa(unsigned int n, int *len_arg, char c)
{
	char	*base;

	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n > 15)
		ft_puthexa(n / 16, len_arg, c);
	ft_putchar(base[n % 16]);
	*len_arg += 1;
}

int	ft_type_p(int *len_arg, unsigned long int p)
{
	if (!p)
	{
		ft_putstr("(nil)");
		return (5);
	}
	write(2, "0x", 2);
	ft_putvoid(p, len_arg);
	*len_arg += 2;
	return (*len_arg);
}

void	ft_putvoid(unsigned long int n, int *len_arg)
{
	char	*base;

	base = "0123456789abcdef";
	if (n > 15)
		ft_putvoid(n / 16, len_arg);
	ft_putchar(base[n % 16]);
	*len_arg += 1;
}

int	ft_putnbr(int nb)
{
	int	n;

	n = nb;
	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
		return (nb);
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	n %= 10;
	ft_putchar(n + '0');
	return (nb);
}

void	ft_putnbr_unsigned(unsigned int n, int *len_arg)
{
	if (n > 9)
		ft_putnbr_unsigned(n / 10, len_arg);
	n %= 10;
	ft_putchar(n + '0');
	*len_arg += 1;
}
