/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:30:04 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/28 01:03:53 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;
	unsigned int	len_s;

	len_s = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start >= len_s || len == 0)
		return (ft_strdup(""));
	if (start + len > len_s)
			len = len_s - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (i < len && i < len_s)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

// #include "stdio.h"

// int	main(void)
// {
// 	char const str[10] = "42";
// 	printf("%s",ft_substr("42", 0 , 0));
// 	return(0);
// }
