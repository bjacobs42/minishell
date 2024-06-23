/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:45:28 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/25 16:26:45 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*content;

	head = NULL;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		else
			content = lst->content;
		if (!content && f)
			return (ft_lstclear(&head, del), NULL);
		new = ft_lstnew(content);
		if (!new)
		{
			if (del)
				del(content);
			return (ft_lstclear(&head, del), NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
