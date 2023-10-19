/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:34:55 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/15 22:27:04 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int c)
{
	size_t	i;
	char	ch;
	char	*s;

	ch = (char)c;
	s = (char *)str;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (!ch && s[i] == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main(void)
{
	char str[8] = "avion";
	printf("%s", ft_strchr(str, 'i'));
	printf("\n%s", strchr(str, 'i'));
	return 0;
}
*/
