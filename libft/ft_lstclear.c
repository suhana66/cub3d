/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:48:48 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 13:10:53 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_delete;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		to_delete = *lst;
		*lst = to_delete->next;
		del(to_delete->content);
		free(to_delete);
	}
	*lst = NULL;
}
