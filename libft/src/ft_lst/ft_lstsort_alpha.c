/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:40:12 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/25 16:41:52 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort_alpha(t_list *list)
{
	t_list	*first;
	t_list	*second;

	first = list;
	while (first)
	{
		second = first->next;
		while (second)
		{
			if (ft_strncmp((char *)first->content, (char *)second->content, \
				ft_strlen((char *)first->content)) > 0)
			{
				ft_memswap(&first->content, &second->content);
			}
			second = second->next;
		}
		first = first->next;
	}
}
