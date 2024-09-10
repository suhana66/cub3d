/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:52:15 by susajid           #+#    #+#             */
/*   Updated: 2024/04/29 17:07:01 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -sign;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (int)((*str - 48) * sign);
		str++;
	}
	if (sign == -1 && result > 0)
		return (0);
	else if (sign == 1 && result < 0)
		return (-1);
	return ((int)result);
}
