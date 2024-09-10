/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:52:55 by susajid           #+#    #+#             */
/*   Updated: 2024/04/18 11:57:57 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*if_found(char needleend, char *result)
{
	if (needleend == 0)
		return (result);
	return (NULL);
}

static char	*find_needle(const char *haystack, const char *needle, size_t len)
{
	char	*result;
	size_t	needlei;
	size_t	i;

	result = NULL;
	needlei = 0;
	i = 0;
	while (i < len && haystack[i] && needle[needlei])
	{
		if (needle[needlei] != haystack[i] && result != NULL)
		{
			result = NULL;
			i -= needlei - 1;
			needlei = 0;
		}
		if (needle[needlei] == haystack[i])
		{
			if (result == NULL)
				result = (char *)(haystack + i);
			needlei++;
		}
		i++;
	}
	return (if_found(needle[needlei], result));
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char *)haystack);
	return (find_needle(haystack, needle, len));
}
