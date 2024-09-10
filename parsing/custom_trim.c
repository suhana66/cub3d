/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:08:05 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/10 18:16:30 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*custom_trim(char const *s1, char const *set, int side)
{
	int		start;
	int		len;
	int		i;

	i = 0;
	while (side <= 1 && s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	len = 0;
	if (s1[i])
	{
		i = ft_strlen(s1) - 1;
		while (side >= 1 && s1[i] && ft_strchr(set, s1[i]))
			i--;
		len = i - start + 1;
	}
	return (ft_substr(s1, start, len));
}
