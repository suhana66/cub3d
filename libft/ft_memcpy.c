/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:52:33 by susajid           #+#    #+#             */
/*   Updated: 2024/04/29 20:24:53 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*result;

	if (!dst && !src)
		return (NULL);
	result = dst;
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (result);
}
