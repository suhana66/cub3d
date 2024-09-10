/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:51:31 by susajid           #+#    #+#             */
/*   Updated: 2024/04/30 14:30:25 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	**current;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	current = &start;
	while (lst)
	{
		content = f(lst->content);
		*current = ft_lstnew(content);
		if (!*current)
			return (del(content), ft_lstclear(&start, del), NULL);
		current = &((*current)->next);
		lst = lst->next;
	}
	return (start);
}
