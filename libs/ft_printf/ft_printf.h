/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:29:00 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/26 20:13:09 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_putnbr(int nb);
int		ft_putstr(char *s);
int		ft_type_p(int *len_arg, unsigned long int p);
int		ft_putchar(int c);
int		count_len(int n);
int		ft_type(char c, va_list arg);
int		ft_printf(const char *format, ...);
void	ft_puthexa(unsigned int n, int *len_arg, char c);
void	ft_putvoid(unsigned long int n, int *len_arg);
void	ft_putnbr_unsigned(unsigned int n, int *len_arg);

#endif
