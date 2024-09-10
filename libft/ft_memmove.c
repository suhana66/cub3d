/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:54:26 by susajid           #+#    #+#             */
/*   Updated: 2024/04/29 20:23:24 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// replace backwards when src before destination
// eg. ft_memmove(dest + 3, dest, 4);
// memory address + 3 = 4th character,
// therefore len - 1 as addition to memory address when replacing backwards
// by default, replace in forward direction
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	int		direction;

	if (!dst && !src)
		return (NULL);
	i = 0;
	direction = 1;
	if (src < dst)
	{
		i = len - 1;
		direction = -1;
	}
	while (len)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i += direction;
		len--;
	}
	return (dst);
}
