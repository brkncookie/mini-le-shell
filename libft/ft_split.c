/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:38:56 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:38:57 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	words_num(const char *s, char c)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			count++;
			trigger = 1;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (count);
}

static void	ft_free(char **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free (arr);
}

static int	fill_arr(char **arr, char *s, char c)
{
	int	len;
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			arr[i] = ft_substr(s - len, 0, len);
			if (!arr[i])
			{
				ft_free(arr, i);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	arr[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (words_num(s, c) + 1));
	if (!arr)
		return (NULL);
	if (!fill_arr(arr, (char *)s, c))
		return (NULL);
	return (arr);
}

// int main()
// {
// 	int i = 0;
// 	char **arr = ft_split("bruh u    hate     this", ' ');
// 	while (i < 5)
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}
// }
