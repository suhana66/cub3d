/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:41:41 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 09:50:21 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// array index + 1 = length
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	int		i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	len = 0;
	if (s1[i])
	{
		i = ft_strlen(s1) - 1;
		while (s1[i] && ft_strchr(set, s1[i]))
			i--;
		len = i - start + 1;
	}
	return (ft_substr(s1, start, len));
}
