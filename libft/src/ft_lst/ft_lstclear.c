/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:45:12 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/06 15:40:41 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*fptr;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		fptr = ptr;
		ptr = ptr->next;
		ft_lstdelone(fptr, del);
	}
	*lst = NULL;
}
