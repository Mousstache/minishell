/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 03:06:35 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/15 22:19:26 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//int	ft_putnbr(int nb);
//void	ft_puthexa(unsigned int n, int *len_arg, char c);
//void	ft_putvoid(unsigned long int n, int *len_arg);
//void	ft_putnbr_unsigned(unsigned int n, int *len_arg);

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}

int	count_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0 || n == 0)
	{
		len = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_type(char c, va_list arg)
{
	int					len_arg;
	unsigned long int	p;

	len_arg = 0;
	if (c == 'c')
		len_arg = ft_putchar((int)va_arg(arg, int));
	if (c == 's')
		len_arg = ft_putstr((char *)va_arg(arg, char *));
	if (c == 'd' || c == 'i')
		len_arg = count_len(ft_putnbr(((int)va_arg(arg, int))));
	if (c == 'u')
		ft_putnbr_unsigned((unsigned int)va_arg(arg, unsigned int), &len_arg);
	if (c == '%')
		len_arg = ft_putchar('%');
	if (c == 'x' || c == 'X')
		ft_puthexa((unsigned int)va_arg(arg, unsigned int), &len_arg, c);
	if (c == 'p')
	{
		p = va_arg(arg, unsigned long int);
		len_arg = ft_type_p(&len_arg, p);
	}
	return (len_arg);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	arg;
	char	*str;

	len = 0;
	i = 0;
	str = (char *)format;
	va_start(arg, format);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
			len = len + ft_type(str[++i], arg);
		else
		{
			ft_putchar(str[i]);
			len++;
		}
		i++;
	}
	return (va_end(arg), len);
}

// int	main(void)
// {
// 	int		a;
// 	void	*p;

// 	p = NULL;
// 	//ft_printf(NULL);
// 	printf("\nretour = %d\n", ft_printf(NULL));
// 	write(1, "\n", 1);
// 	printf("\nretour_du_vrai = %d\n", printf(NULL));
// 	return (0);
// }
