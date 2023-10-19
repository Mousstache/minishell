/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:50 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/21 01:59:54 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*to_find;
	char	*str;

	if (s2[0] == '\0')
		return ((char *)s1);
	if (!len)
		return (NULL);
	to_find = (char *)s2;
	str = (char *)s1;
	i = -1;
	j = 0;
	while (str[++i] && i < len && j < len)
	{
		if (str[i] == to_find[j])
		{
			while (to_find[j] && (str[i + j] == to_find[j]) && i + j < len)
				j++;
			if (to_find[j] == '\0')
				return (&str[i]);
			j = 0;
		}
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
	char str[] = "aaabcabcd";
	char str2[] = "cd";
	printf("%s", ft_strnstr(str, str2, 8));
	//printf("\n%d", strnstr(str, str2, 8));
	return 0;
}
*/
