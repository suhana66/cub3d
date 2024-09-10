/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:23:40 by susajid           #+#    #+#             */
/*   Updated: 2024/03/26 14:31:20 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*srcstart;
	size_t		dstlen;

	srcstart = src;
	dstlen = ft_strlen(dst);
	dst += dstlen;
	if (dstsize && dstlen < dstsize)
	{
		while (*src && --dstsize - dstlen)
			*dst++ = *src++;
		*dst = 0;
	}
	else
		dstlen = dstsize;
	return ((size_t)(ft_strlen(srcstart) + dstlen));
}
