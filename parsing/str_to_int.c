/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:25:07 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/10 19:43:19 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	isoutlimit(long num, char c)
{
	if (num > 25 || (num == 25 && (c - '0') > 5))
		return (1);
	else
		return (0);
}

int	str_to_int(const char *str, int *error)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			*error = 1;
	}
	if (str[i] < '0' || str[i] > '9')
		*error = 1;
	result = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (isoutlimit(result, str[i])
			|| (str[i + 1] && (str[i + 1] < '0' || str[i + 1] > '9')))
			return (*error = 1, 0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
