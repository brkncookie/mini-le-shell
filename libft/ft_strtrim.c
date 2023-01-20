/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:43 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:44 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	outstr_size;
	int				start;
	int				end;
	char			*outstr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && is_in_set(s1[i], set))
		i--;
	end = i;
	if (end < start)
		return (ft_strdup(""));
	outstr_size = end - start + 1;
	outstr = ft_substr(s1, start, outstr_size);
	return (outstr);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s\n", ft_strtrim("ABABABBXABABABAB", "AB"));
// }
