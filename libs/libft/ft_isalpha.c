/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:22:52 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/15 20:55:08 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (!(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z'))
		return (0);
	else
		return (1);
}
/*
int	main(void)
{
	printf("%d",ft_is_alpha('J'));
	printf("\n%d", isalpha('J'));
	return 0;
}
*/
