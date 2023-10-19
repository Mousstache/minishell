/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:17:17 by maheraul          #+#    #+#             */
/*   Updated: 2022/11/18 02:13:46 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

int	cc_tichar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

int	ft_len_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (cc_tichar(s1[i], set))
			i++;
		if (s1[i] == '\0' || !(cc_tichar(s1[i], set)))
			break ;
	}
	return (i);
}

int	ft_len_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (s1[i])
		i++;
	i--;
	while (i > 0)
	{
		if (cc_tichar(s1[i], set))
		{
			i--;
			end++;
		}
		if (s1[i] == '\0' || !(cc_tichar(s1[i], set)))
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!set)
		return ((char *)s1);
	start = ft_len_start(s1, set);
	end = ft_len_end(s1, set);
	len = (ft_strlen(s1) - (start + end));
	if ((int)len < 0)
		return (ft_strdup(""));
	trim = ft_substr(s1, start, len);
	return (trim);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *s = ft_strtrim("abcdba", "acb");
// 	printf("%c", s[0]);
// 	printf("%c", s[1]);
// 	free(s);
// 	return(0);
// }
