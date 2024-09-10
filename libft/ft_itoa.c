/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:50:13 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 13:51:03 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digicount(int n)
{
	int	result;

	result = 0;
	if (n <= 0)
		result++;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;
	int		sign;

	count = digicount(n);
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[count] = '\0';
	sign = 1;
	if (n < 0)
		sign = -1;
	while (count)
	{
		count--;
		if (count == 0 && sign == -1)
			result[count] = '-';
		else
			result[count] = (char)(n % 10 * sign + '0');
		n /= 10;
	}
	return (result);
}
