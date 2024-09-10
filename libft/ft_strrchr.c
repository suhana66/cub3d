/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:55:15 by susajid           #+#    #+#             */
/*   Updated: 2024/04/29 19:59:24 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	c = c % 256;
	result = NULL;
	while (1)
	{
		if (*s == c)
			result = ((char *)(s));
		if (!*s)
			break ;
		s++;
	}
	return (result);
}
