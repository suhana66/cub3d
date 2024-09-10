/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:00:00 by susajid           #+#    #+#             */
/*   Updated: 2024/05/10 19:22:58 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strcount(char const *s, char c)
{
	int	result;
	int	flag;

	result = 0;
	flag = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else if (!flag)
		{
			flag = 1;
			result++;
		}
		s++;
	}
	return (result);
}

char	**check_mallocs(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!array[i])
		{
			i = 0;
			while (i < size)
				free(array[i++]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}

// HOW TO CREATE AN ARRAY OF STRINGS IN C (NO NEED TO CHANGE)?
// const char *a[2];
// a[0] = "blah";
// a[1] = "hmm";
// 3 malloc calls
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		arr_len;
	int		i;
	int		j;

	arr_len = strcount(s, c);
	result = malloc((arr_len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[arr_len] = NULL;
	i = 0;
	while (i < arr_len)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		result[i++] = ft_substr(s, 0, j);
		s += j;
	}
	return (check_mallocs(result, arr_len));
}
