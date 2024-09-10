/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:06:17 by susajid           #+#    #+#             */
/*   Updated: 2024/03/25 16:22:47 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*srcstart;

	srcstart = src;
	if (dstsize)
	{
		while (*src && --dstsize)
			*dst++ = *src++;
		*dst = 0;
	}
	return (ft_strlen(srcstart));
}
