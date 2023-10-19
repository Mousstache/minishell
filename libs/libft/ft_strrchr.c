/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:39:50 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/15 22:30:54 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;

	str = (char *)s;
	ch = (char)c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (s[i] == (char)ch)
			return ((char *)&str[i]);
		i--;
	}
	if (!ch && str[i] == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

// int main(void)
// {
// 	char *str = "tripouille";
// 	printf("%s", ft_strrchr(str, 't'));
// 	// printf("\n%s", strrchr(str, 'i'));
// 	return 0;
// }
